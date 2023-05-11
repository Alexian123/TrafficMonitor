import os

# in the order they should be included
LIBRARIES = ['TrafficMonitor', 'TrafficLight', 'IntersectionControl', 'SerialHandler']
INO_FILE_PATH = './examples/Intersection/Intersection.ino'

src_path = './src/'
headers = [src_path + lib + '.h' for lib in LIBRARIES]
sources = [src_path + lib + '.cpp' for lib in LIBRARIES[1:]]

for h in headers:
    with open(h, 'r') as f:
        lines = f.readlines()
        for l in lines:
            if l.startswith('#pragma') or l.startswith('#include'):
                continue
            print(l)
  
for s in sources:
    with open(s, 'r') as f:
        lines = f.readlines()
        for l in lines:
            if l.startswith('#include'):
                continue
            print(l)
            
with open(INO_FILE_PATH, 'r') as f:
    lines = f.readlines()
    for l in lines:
        if l.startswith('#include'):
            continue
        print(l)