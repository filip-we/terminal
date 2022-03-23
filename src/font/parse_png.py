from PIL import Image
from sys import argv, exit

def get_graphical_string(image_name, check=(255, 255, 255)):
    im = Image.open(image_name, 'r')
    width, height = im.size
    pixels = list(im.getdata())
    s = ''
    for h in range(height):
        for w in range(width):
            p = pixels[w + h * width]
            s += chr(0x25A0) if p == check else ' '
        s+= '\n'
    return s

def convert_image_to_bytemap(image_name, check=(255, 255, 255)):
    im = Image.open(image_name, 'r')
    width, height = im.size
    pixels = list(im.getdata())
    all_bytes = list()
    current_byte = 0
    n = 0
    for h in range(height):
        for w in range(width):
            p = pixels[w + h * width]
            current_byte = (current_byte << 1) + int(p == check)
            n += 1
            if n == 8:
                all_bytes.append(current_byte)
                current_byte = 0
                n = 0
    return bytearray(all_bytes)

if __name__ == '__main__':
    if len(argv) < 2:
        print('Please supply an image!')
        exit(1)

    all_bytes = convert_image_to_bytemap(argv[1])
    with open(argv[1] + '.bin', 'wb') as fb:
        fb.write(all_bytes)

    print(get_graphical_string(argv[1]))
