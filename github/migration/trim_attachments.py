import glob
import json
from pathlib import Path
import argparse


def load_attachments_json(file_paths: list[str]) -> list[dict]:
    """Load and merge attachment data from multiple JSON files."""
    attachments = []
    for file_path in file_paths:
        with open(file_path, 'r') as f:
            loaded = json.load(f)
            assert all(x['type'] == 'attachment' for x in loaded)
            attachments += loaded
    return attachments


def save_attachments_json(out_dir: str, attachments: list[dict]):
    """Save attachment data to a JSON file."""
    # For each 50 itesm of attachments,  save to a separate file, e.g., attachments_0000001.json
    # attachments_0000002.json, etc.
    for i in range(0, len(attachments), 50):
        file_path = f"{out_dir}/attachments_{i // 50 + 1:06d}.json"
        to_save = attachments[i:i + 50]
        with open(file_path, 'w') as f:
            json.dump(to_save, f, indent=2)
        print(f"Saved {len(to_save)} attachments to {file_path}")


def analyze_attachments(meta_archive_dir: Path, attachments: list[dict]) -> list[tuple[dict, Path, int]]:
    """Sort attachments by size."""
    records = []
    for attachment in attachments:
        tarball_prefix = 'tarball://root/'
        asset_url = attachment['asset_url']
        assert asset_url.startswith(tarball_prefix)
        asset_path = meta_archive_dir / asset_url.removeprefix(tarball_prefix)
        size = asset_path.stat().st_size
        records.append((attachment, asset_path, size))

    # Sort by size in descending order
    return sorted(records, key=lambda x: x[1], reverse=True)


def main():
    parser = argparse.ArgumentParser(description='Analyze and filter attachments by size')
    parser.add_argument('meta_archive_dir', type=str, help='Extracted directory of the meta archive')
    parser.add_argument('out_dir', type=str, help='Output directory')
    args = parser.parse_args()

    print("Loading attachments...")
    attachments_jsons = glob.glob(f"{args.meta_archive_dir}/attachments_*.json")
    attachments = load_attachments_json(attachments_jsons)
    print(f"Found {len(attachments)} attachments from {len(attachments_jsons)} JSON files")

    print("Analyzing attachment sizes...")
    attachments_with_size = analyze_attachments(Path(args.meta_archive_dir), attachments)

    # Print size summary
    total_size = sum(a[2] for a in attachments_with_size)
    print(f"Total size of all attachments: {total_size / (1024**3):.2f} GB")

    # Filter attachments if total size exceeds 19GB
    removed_attachments_with_size = []
    removed_size = 0
    while total_size > (19 * (1024**3)):
        to_remove = attachments_with_size[0]
        removed_size += to_remove[2]
        removed_attachments_with_size.append(to_remove)
        attachments_with_size = attachments_with_size[1:]
        total_size = sum(a[2] for a in attachments_with_size)

    print(f"Removed attachments: {removed_size / (1024**3):.2f} GB, {len(removed_attachments_with_size)} attachments")
    print(f"Remaining attachments: {total_size / (1024**3):.2f} GB, {len(attachments_with_size)} attachments")

    # Remove the removed attachments from the original list
    save_attachments_json(args.out_dir, [x[0] for x in attachments_with_size])

    print("Now run these commands:")
    print(f"rm {args.meta_archive_dir}/attachments_*.json")
    print(f"mv {args.out_dir}/attachments_*.json {args.meta_archive_dir}")
    print("process() { rm $1; }")
    for attachment in removed_attachments_with_size:
        print('process', attachment[1])


if __name__ == '__main__':
    main()
