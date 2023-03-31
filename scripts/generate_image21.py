from random import random

lines = """\
A	1.0	220,235,255
C	13,2,3	-0.9636241116594315,-0.14824986333222023,-0.22237479499833035	37

sp	0,-1000,0	2000	128,128,128
sp	-4,1,0	2	104,52,26
sp	0,1,0	2	128,128,128
sp	4,1,0	2	182,156,130""".split(
    "\n"
)

for a in range(-11, 11):
    for b in range(-11, 11):
        while True:
            x = a + 0.9 * random()
            y = 0.2
            z = b + 0.9 * random()
            dy = (y - 0.2) ** 2
            dz = z**2
            if all((x - sx) ** 2 + dy + dz > 0.9 for sx in (-4, 0, 4)):
                break
        lines.append(f"sp\t{x:.3f},{y:.3f},{z:.3f}\t0.4\t255,255,255")


open("scenes/valid/image21.rt", "w").write("\n".join(lines))
