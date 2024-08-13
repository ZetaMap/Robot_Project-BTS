#include "fanucrobotcontrol.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

FanucRobotControl::FanucRobotControl(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setupModbus();

    // Setup timer for periodic update of UOP values
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &FanucRobotControl::updateUopValuesPeriodically);
    updateTimer->start(1000); // Update every second
}

FanucRobotControl::~FanucRobotControl()
{
    if (modbusContext != nullptr)
        modbus_free(modbusContext);
}

void FanucRobotControl::setupUi()
{
    // Setup UI components
    ipAddressLineEdit = new QLineEdit(this);
    connectButton = new QPushButton("Connect", this);
    startButton = new QPushButton("Start Program", this);
    pauseButton = new QPushButton("Pause Program", this);
    stopButton = new QPushButton("Stop Program", this);
    statusLabel = new QLabel("", this);
    uopStatusLabel = new QLabel("", this);

    // Connect signals and slots
    connect(connectButton, &QPushButton::clicked, this, &FanucRobotControl::connectToRobot);
    connect(startButton, &QPushButton::clicked, this, &FanucRobotControl::startProgram);
    connect(pauseButton, &QPushButton::clicked, this, &FanucRobotControl::pauseProgram);
    connect(stopButton, &QPushButton::clicked, this, &FanucRobotControl::stopProgram);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Robot IP Address:", this));
    layout->addWidget(ipAddressLineEdit);
    layout->addWidget(connectButton);
    layout->addWidget(startButton);
    layout->addWidget(pauseButton);
    layout->addWidget(stopButton);
    layout->addWidget(statusLabel);
    layout->addWidget(uopStatusLabel);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void FanucRobotControl::setupModbus()
{
    // Initialize Modbus context
    modbusContext = modbus_new_tcp(ipAddress.toStdString().c_str(), modbusServerPort);
    if (modbusContext == nullptr) {
        statusLabel->setText("Unable to create Modbus context: " + QString(modbus_strerror(errno)));
        return;
    }

    // Connect to Modbus server
    if (modbus_connect(modbusContext) == -1) {
        statusLabel->setText("Modbus connection failed: " + QString(modbus_strerror(errno)));
        modbus_free(modbusContext);
        modbusContext = nullptr;
        return;
    }

    statusLabel->setText("Modbus connection successful");
}

void FanucRobotControl::connectToRobot()
{
    // Retrieve IP address and port
    ipAddress = ipAddressLineEdit->text();
    modbusServerPort = 502; // Default Modbus TCP port

    // Setup Modbus context
    setupModbus();
}

void FanucRobotControl::startProgram()
{
    // Write start program command to Modbus address for RSR1/PNS1 (UI 9)
    uint16_t startCommand = 1; // Value to start the program
    int rc = modbus_write_register(modbusContext, 105, startCommand); // Assuming RSR1/PNS1 is at address 105
    if (rc == -1) {
        statusLabel->setText("Error starting program: " + QString(modbus_strerror(errno)));
    } else {
        statusLabel->setText("Program started successfully");
    }
}

void FanucRobotControl::pauseProgram()
{
    // Write pause program command to Modbus address for HOLD (UI 2)
    uint16_t pauseCommand = 1; // Value to pause the program
    int rc = modbus_write_register(modbusContext, 98, pauseCommand); // Assuming HOLD is at address 98
    if (rc == -1) {
        statusLabel->setText("Error pausing program: " + QString(modbus_strerror(errno)));
    } else {
        statusLabel->setText("Program paused successfully");
    }
}

void FanucRobotControl::stopProgram()
{
    // Write stop program command to Modbus address for CSTOPI (UI 4)
    uint16_t stopCommand = 1; // Value to stop the program
    int rc = modbus_write_register(modbusContext, 100, stopCommand); // Assuming CSTOPI is at address 100
    if (rc == -1) {
        statusLabel->setText("Error stopping program: " + QString(modbus_strerror(errno)));
    } else {
        statusLabel->setText("Program stopped successfully");
    }
}

void FanucRobotControl::updateUopValuesPeriodically()
{
    // Read UOP values from Modbus
    int rc = modbus_read_registers(modbusContext, uopStartAddress, uopNumWords, reinterpret_cast<uint16_t*>(uopValues.data()));
    if (rc == -1) {
        statusLabel->setText("Error reading UOP values: " + QString(modbus_strerror(errno)));
        return;
    }

    // Update UOP status label
    QString uopStatusText;
    for (int i = 0; i < uopNumWords; ++i) {
        uopStatusText += QString("UOP%1: %2\n").arg(i + 1).arg(uopValues[i]);
    }
    uopStatusLabel->setText(uopStatusText);
}
