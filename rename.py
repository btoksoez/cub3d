import os

def update_include_lines(directory, old_include, new_include):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".c"):
                file_path = os.path.join(root, file)

                with open(file_path, 'r') as f:
                    lines = f.readlines()

                with open(file_path, 'w') as f:
                    for line in lines:
                        if line.strip() == old_include:
                            f.write(new_include + '\n')
                        else:
                            f.write(line)

if __name__ == "__main__":
    sources_bonus_directory = 'sources_bonus'
    old_include_line = '#include "../../includes/cub3d.h"'
    new_include_line = '#include "../../includes_bonus/cub3d.h"'

    update_include_lines(sources_bonus_directory, old_include_line, new_include_line)
    print("Include lines updated successfully.")
