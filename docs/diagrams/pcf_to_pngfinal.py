import pathlib
import subprocess

def parse_pcf(path):
    diagrams = {}
    name = None
    payload = []
    in_payload = False

    with open(path, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.rstrip('\n')

            if line.startswith("BEGIN_DIAGRAM"):
                name = line.split(" ", 1)[1]
                payload = []

            elif line.startswith("PAYLOAD_START"):
                in_payload = True

            elif line.startswith("PAYLOAD_END"):
                in_payload = False
                diagrams[name] = "\n".join(payload)

            elif in_payload:
                payload.append(line)

    return diagrams


def render_tama_to_png(name, tama_text, out_dir="out"):
    out_dir = pathlib.Path(out_dir)
    out_dir.mkdir(exist_ok=True)

    tama_file = out_dir / (name + ".tama")
    png_file = out_dir / name

    with open(tama_file, "w", encoding="utf-8") as f:
        f.write(tama_text)

    # Replace "tama-render" with your actual renderer command
    subprocess.run(["tama-render", str(tama_file), "-o", str(png_file)], check=True)


def main():
    diagrams = parse_pcf("diagrams.pcf")
    for name, payload in diagrams.items():
        render_tama_to_png(name, payload)


if __name__ == "__main__":
    main()
