if [[ "$1" == "" ]]; then
  echo "No input directory specified to generate python stubs packages"
  exit 2
fi

if [[ "$2" == "" ]]; then
  echo "No output directory specified for generated stubs"
  exit 2
fi

if [[ "$(which pybind11-stubgen)" = "" ]] then
  if [[ "$(which pip3)" = "" ]]; then
    echo "ERROR: python package manager not found. Please install it."
    exit 3
  fi
  echo "WARNING: pybind11-stubgen command not found. Installing library..."
  pip3 install pybind11-stubgen
fi


dir="$1/"
OLD_PYTHONPATH="$PYTHONPATH"
trap 'export PYTHONPATH="$OLD_PYTHONPATH";exit 1' INT QUIT ABRT KILL
export PYTHONPATH="$dir"

#for i in $(find "$dir" -type d -not -name "*.egg-info" -not -name "__pycache__"); do 
#  # extract module name
#  package="${i#""$dir""}"
#  module="${package//\//.}"
#  [ "$module" == "" ] && continue
#  # generate stubs
#  echo "generating stubs for module: $module"
#  pybind11-stubgen --stub-extension py -o "$2" "$module" 
#  # make generated stubs, as a valid module
#  [ -f "$2/$module.py" ] && mkdir -p "$2/$module" && mv "$2/$module.py" "$2/$module/__init__.py"
#  # remove unwanted part in files
#  if [[ -d "$2/$module" ]]; then
#    for i in $(find "$2/$module" -type f -name "*.py"); do
#      sed -i -e "s/^from __future__ import annotations.*$//g" -e "s/^__all__ = list().*$//g" "$i"
#    done  
#  fi
#done

#args=""
#for i in $(find "$dir" -maxdepth 1 -type d -not -name "*.egg-info" -not -name "__pycache__"); do 
#  # extract module name
#  package="${i#""$dir""}"
#  module="${package//\//.}"
#  [ "$module" == "" ] && continue
#  args="$args -p $module"
#done
#
#stubgen --inspect --include-private --include-docstrings -o "$2" $args

for i in $(find "$dir" -maxdepth 1 -type d -not -name "*.egg-info" -not -name "__pycache__"); do
  package="${i#""$dir""}"
  [ "$package" == "" ] && continue
  echo "generating stubs for module: $package"
  stubgen --no-import --include-private --include-docstrings -o "$2" $i
done

export PYTHONPATH="$OLD_PYTHONPATH"
echo -e "\nDone!"
