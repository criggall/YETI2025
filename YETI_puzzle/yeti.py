# Read in transmission:
with open("transmission.jpg", "rb") as f:
    transmission = f.read()

# Read in control image:
with open("test_image.jpeg", "rb") as f:
    control = f.read()

''' The transmission is sent in 16-bit chunks, so chunks of 2 bytes. 
Comparing the header of the transmission to a control image, 
it appears that each 2-byte chunk has been scrambled according to
this pattern: AB->BA. To unscramble, let us loop over each chunk
and undo the scrambling per the transmformation: BA->AB. '''

# Unscramble:
count = 0
unscrambled = b''
for i in range(int(len(transmission)/2)):
    unscrambled += transmission[count+1:count+2]
    unscrambled += transmission[count:count+1]
    count += 2

''' The prompt says there were 5 images expected.
Let us loop over the length of the transmission to check for
end-of-image tags and write out each image present. '''

# Separate and write out images:
current_image = b''
start = 0
count = 1
for i in range(int(len(unscrambled))-1):
     if unscrambled[i:i+2] == b'\xff\xd9':
         current_image = unscrambled[start:i+2]
         start = i+2
         with open(f'image{count}.jpeg', 'wb') as f:
              f.write(current_image)
         count += 1