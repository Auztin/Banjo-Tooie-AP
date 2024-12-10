source_path = 'ap-icon.data'
dest_path = 'ap-icon.btimg'
width = 32
height = 32
with open(source_path, 'rb') as source_file:
  source = bytes(source_file.read())
  dest = bytearray(b'\0'*(width*height*2))
  for y in range(height):
    for x in range(width):
      si = y*width+x
      si *= 4
      di = (height-y-1)*width+x
      di *= 2
      red = source[si]
      green = source[si+1]
      blue = source[si+2]
      alpha = source[si+3]
      red = int(red/255.0*31)
      green = int(green/255.0*31)
      blue = int(blue/255.0*31)
      alpha = 1 if alpha else 0
      pixel = red << 11
      pixel |= green << 6
      pixel |= blue << 1
      pixel |= alpha
      dest[di] = pixel >> 8
      dest[di+1] = pixel & 0xFF
  with open(dest_path, 'wb') as dest_file:
    dest_file.write(dest)
