"""
Re-implementation of niryo_robot_modbus.modbus_server, for own use
"""

from util.logger import Logger
from util.errors import ModbusServerError
from util.vars import (
  MODBUS_SERVER_ADDRESS,
  MODBUS_SERVER_PORT,
  MODBUS_IDENTITY_VENDOR_NAME,
  MODBUS_IDENTITY_VENDOR_URL,
  MODBUS_IDENTITY_PRODUCT_NAME,
  MODBUS_IDENTITY_MODEL_NAME,
  MODBUS_IDENTITY_REVISION
)

from threading import Thread

from pymodbus.server.sync import ModbusTcpServer
from pymodbus.device import ModbusDeviceIdentification
from pymodbus.datastore import ModbusSlaveContext, ModbusServerContext

from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

from .input_register import InputRegisterDataBlock
from .holding_register import HoldingRegisterDataBlock

__all__ = [
  "ModbusServer"
]


class ModbusServer:  
  def __init__(self, robot: NiryoRosWrapper):
    self.logger = Logger(__class__.__name__)
    self.thread = None

    self.input_register = InputRegisterDataBlock(robot)
    self.holding_register = HoldingRegisterDataBlock(robot)
    self.store = ModbusSlaveContext(hr=self.holding_register, ir=self.input_register)
    self.context = ModbusServerContext(slaves=self.store, single=True)

    self.identity = ModbusDeviceIdentification()
    self.identity.VendorName = MODBUS_IDENTITY_VENDOR_NAME
    self.identity.VendorUrl = MODBUS_IDENTITY_VENDOR_URL
    self.identity.ProductName = MODBUS_IDENTITY_PRODUCT_NAME
    self.identity.ModelName = MODBUS_IDENTITY_MODEL_NAME
    self.identity.MajorMinorRevision = MODBUS_IDENTITY_REVISION

    try: self.server = ModbusTcpServer(context=self.context, framer=None, identity=self.identity, 
                                       address=(MODBUS_SERVER_ADDRESS, MODBUS_SERVER_PORT),
                                       allow_reuse_address=True)
    except OSError as err:
      message = "TCP server unable to start: " + str(err)
      self.logger.err(message)
      raise ModbusServerError(message)
    self.logger.info("Created server")

  def start(self):
    if self.thread and self.thread.is_alive(): raise ModbusServerError("server already started")
    self.thread = Thread(target=self.server.serve_forever, name="NiryoModbusServer", daemon=True)
    self.thread.start()
    self.logger.info("Started server")

  def stop(self):
    if not self.thread  or not self.thread.is_alive(): raise ModbusServerError("server not started")
    self.logger.info("Closing server")
    self.server.shutdown()
    self.thread.join(10)
    self.server.server_close()
    if not self.thread.is_alive(): self.logger.info("Stopped server")
    else: self.logger.warn("Timeout when stopping server")
    self.thread = None
    