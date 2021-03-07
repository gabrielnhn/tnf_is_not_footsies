import sys
import os

def sort_key(x):
    return int(x.split(".")[0])


for possible_dir in sorted(os.listdir(".")):
    if os.path.isdir(possible_dir): # exactly what we're looking for
        
        for file in sorted(os.listdir(possible_dir), key=sort_key):
            index = int(file.split(".")[0])
            os.rename(os.path.join(possible_dir, file), os.path.join(possible_dir,"{}.png".format(index - 1)))

# os.rename()