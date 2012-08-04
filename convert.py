import os

list1 = []
#os.chdir("OpenFOAM-2.1.x")
n = 0
for dirname, dirnames, filenames in os.walk("OpenFOAM-2.1.x"):#."):
    for name in filenames:
        if len(name) > 1 and name[-2] == ".":
            if name[-1] == "C" or name[-1] == "H":
                list1 += [(name, dirname)]

#this assumes elements only differ by one letter
list2 = []
for entry, dir in list1:
	for comparison, compDir in list1:
		if dir == compDir:
			if entry.lower() == comparison.lower():
				for i in range(len(entry)):
					if(entry[i] != comparison[i]):
						if(entry[i] == comparison[i].lower()):
							list2 += [(dir, entry, entry + "LC")]
							list2 += [(dir, comparison, comparison + "UC")]
						else:						
							list2 += [(dir, comparison, comparison + "LC")]
							list2 += [(dir, entry, entry + "UC")]

print len(list2)