# !/usr/bin/env python3

def clean_pycache(path=".", debug=False):
  """Clean __pycache__ directories recursively. Call this before setup()."""
  import os
  for file in os.listdir(path):
    new_path = os.path.join(path, file)
    if os.path.isdir(new_path): 
      if file == "__pycache__": 
        if debug: print("removing folder: " + new_path)
        # Remove a file or a directory recursively using terminal commands.
        # This way avoid some permissions errors.
        if os.name == "nt": os.system(("rd /s" if os.path.isdir(new_path) else "del /f") + " /q \"" + new_path.replace('/', '\\') + "\"")
        else: os.system("rm -rf \"" + new_path.replace('\\', '/') + "\"")
      else: clean_pycache(new_path)

clean_pycache(__file__[:__file__.rfind("\\")+1 or __file__.rfind("/")+1], True)
