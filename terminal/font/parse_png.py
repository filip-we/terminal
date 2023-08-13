from PIL import Image
from sys import argv, exit

def convert_image_to_bitmap(image_name, check=(255, 255, 255), char_dim=(8, 16)):
    im = Image.open(image_name, 'r')
    width, height = im.size
    nr_chars_per_row = int(width / char_dim[0])
    nr_chars_per_col = int(height / char_dim[1])
    pixels = list(im.getdata())
    all_bytes = list()
    current_char = 0
    n = 0
    for char_y in range(nr_chars_per_col):
        for char_x in range(nr_chars_per_row):
            for h in range(char_dim[1]): # It feels most natural to scan from left to right.
                offset = width * h + char_dim[0] * char_x + char_y * char_dim[0] * char_dim[1]
                for w in range(char_dim[0]):
                    p = pixels[offset + w]
                    current_char = (current_char << 1) + int(p == check)
                    n += 1
                    if n == 8:
                        all_bytes.append(current_char)
                        current_char = 0
                        n = 0
    return bytearray(all_bytes)

def print_char_from_bitmap(file_name, char_nrs, char_dim=(8, 16), image_char_map=(8, 8)):
    area_bits = char_dim[0] * char_dim[1]
    area_bytes = int(char_dim[0] * char_dim[1] / 8)
    s = ''
    with open(file_name, 'rb') as fb:
        for c in char_nrs:
            fb.seek(c * area_bytes)
            data = fb.read(area_bytes)
            print(data)
            for b in data:
                for i in range(8):
                    s += chr(0x25A0) if (b >> i) & 1 else ' '
                s += '\n'
    return s

if __name__ == '__main__':
    if len(argv) < 2:
        print('Please supply an image!')
        exit(1)

    file_name = '.'.join(argv[1].split('.')[:-1])
    with open(file_name + '.bin', 'wb') as fb:
        fb.truncate()
        fb.write(convert_image_to_bitmap(argv[1]))

