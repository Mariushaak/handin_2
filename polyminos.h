//Here you can make your Polyminos of choice. 
//You can draw your polyminos like this and follow the explanation in the comments below
//	0  1  2  3	4  5
//0 
//1    x
//2       x  x  x
//3    x        x
//4
//5

int polyminos(int x, int y, int z) {

	switch (x) {						//x = shape number

	case 0:
		
		switch (y) {					//y = tile number, totalling at 6
		case 0:
			if (z == 1)					//if z = 1 means its the x coordinate of the tile you want
				return 2;				//in this case the tile (2, 0) will be coloured
			return 0;					
		case 1:							
			if (z == 1)					//In this case tile (2,1) will be coloured
				return 2;
			return 1;
		case 2:
			if (z == 1)
				return 2;
			return 2;
		case 3:
			if (z == 1)
				return 2;
			return 3;
		case 4:
			if (z == 1)
				return 2;
			return 4;
		case 5:
			if (z == 1)
				return 2;
			return 5;
		}								//All this sums up to a shape that is 1x6 in size, which is a straigth line
	}
}