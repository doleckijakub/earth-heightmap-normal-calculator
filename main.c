#define world_radius      6371000.0f
#define sea_level         0.0f
#define height_multiplier 1000.0f

#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "stb_image.h"
#include "stb_image_write.h"

typedef unsigned char u8;

int main(int argc, const char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input heightmap> <output>\n", argv[0]);
		return 1;
	}

	const char *input  = argv[1];
	const char *output = argv[2];

	int w, h, n;
	u8 *heightmap = stbi_load(input, &w, &h, &n, 1);
	u8 *normalmap = calloc(w * h, 4);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			float dx = heightmap[n * (y * w + (x + 1) % w)] - heightmap[n * (y * w + (x - 1 + w) % w)];
			float dy = (y == 0 || y == h - 1) 
				? 0
				: heightmap[n * ((y + 1) * w + x)] - heightmap[n * ((y - 1) * w + x)];

			float normal[3] = { -dx, -dy, 1 };
			float length = sqrtf(
				normal[0] * normal[0]
				+ normal[1] * normal[1]
				+ normal[2] * normal[2]
			);
			if (length > 0) {
				normal[0] /= length;
				normal[1] /= length;
				normal[2] /= length;
			}

			normalmap[4 * (x + y * w)]     = (normal[0] + 1.0f) * 127.5f;
			normalmap[4 * (x + y * w) + 1] = (normal[1] + 1.0f) * 127.5f;
			normalmap[4 * (x + y * w) + 2] = (normal[2] + 1.0f) * 127.5f;
			normalmap[4 * (x + y * w) + 3] = heightmap[n * (x + y * w)];
		}

		if (100 * (y - 1) / h != 100 * y / h) {
			printf("%d%%\n", 100 * y / h);
		}
	}

	stbi_image_free(heightmap);

	stbi_write_png(output, w, h, 4, normalmap, 4 * w);

	free(normalmap);

}
