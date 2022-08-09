import cupy

d = cupy.cuda.Device(0)
free, _ = d.mem_info

full = None
for size in range(free, 1, -512*8):
    try:
        full = cupy.empty((size,), dtype=cupy.int8)
        break
    except Exception as e:
        pass

print('alloced:', size)
