# Check if installed
if [[ "$(which pyreverse)" = "" ]]; then
  echo "PyReverse not found! Install it?"
  echo "This will be run these two commands:"
  echo "  sudo apt install graphviz libgraphviz-dev"
  echo "  pip install pylint pygraphviz"
  echo -n "[Y|n] > "
  read choice

  if [[ "$choice" == "" ]] || [[ "$choice" == "y" ]] || [[ "$choice" == "yes" ]]; then
    sudo apt install graphviz libgraphviz-dev && pip install pylint pygraphviz
  else if [[ "$choice" == "n" ]] || [[ "$choice" == "no" ]]; then
    echo "Execution canceled! Exiting."
    exit 1
  else
    echo "Invalid choice! Exiting."
    exit 2
  fi
  fi
fi

# Check arguments
if [[ "$@" == *"--help"* ]]; then
  pyreverse --help
  exit 0
fi
if [[ "$1" == "" ]]; then
  echo "No directory specified"
  exit 4
fi
if [[ "$2" == "" ]]; then
  echo "Empty generator format type. \n"
  pyreverse -o all
  exit 3
fi

# Settings
TEMP_DIR="${TMPDIR:-/tmp}/python-uml-generator/$1"
UML_NAME="$(basename $1)"

# Create an temporary directory
echo "copying files to $TEMP_DIR..."
rm -rf "$TEMP_DIR"
mkdir -p "$TEMP_DIR"
cp -rf "$1" "$TEMP_DIR"

# And run the generator
pyreverse --colorized -m y -Ap "$UML_NAME" -o "$2" $(find "$TEMP_DIR" -name "*.py") ${@:3}