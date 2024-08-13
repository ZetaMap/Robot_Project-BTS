if [[ "$1" == "" ]]; then
  echo "No project name specified"
  exit 2
fi
if [[ "$2" == "" ]]; then
  echo "No output directory specified for generated documentations"
  exit 2
fi
if [[ "$3" == "" ]]; then
  echo "No input directory specified with python code"
  exit 2
fi

if [[ "$(which pydoctor)" = "" ]] then
  if [[ "$(which pip3)" = "" ]]; then
    echo "ERROR: python package manager not found. Please install it."
    exit 3
  fi
  echo "WARNING: pdoc command not found. Installing library..."
  pip3 install pydoctor
fi

pydoctor "$3" ${@:4} --html-output "$2" --project-name "$1" --make-html --docformat "restructuredtext" --theme "readthedocs"
