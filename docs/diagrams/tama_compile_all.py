# tama_compile_all.py
import pathlib
import subprocess

def compile_all_tama(src_dir="out", renderer="tama-render"):
  src_dir = pathlib.Path(src_dir)
  for tama_file in src_dir.glob("*.tama"):
    png_file = tama_file.with_suffix(".png")
    subprocess.run([renderer, str(tama_file), "-o", str(png_file)], check=True)

if __name__ == "__main__":
  compile_all_tama()
