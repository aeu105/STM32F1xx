#ifndef __BMP_H__
#define __BMP_H__


unsigned char Bless[] = {
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x60,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x80,0x00,0x00,0x00,0x00,0x20,0x20,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x05,0x07,0xFE,0x60,
	0x18,0x01,0x87,0xFC,0xC2,0x82,0x82,0xC2,0x62,0x7A,0x0E,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xBE,0x80,
	0x80,0x80,0xC0,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x0F,0x03,0x01,0x41,0x41,0xC1,0x61,0x69,0x29,0x2D,0x05,0x05,0x03,0x03,0x01,
	0x00,0x00,0x00,0xE0,0x00,0x08,0x08,0x88,0x88,0x88,0x88,0x80,0x88,0x88,0x08,0x08,
	0x08,0x08,0x08,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x0C,0x08,
	0x10,0x30,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x60,0x38,0x0E,0x02,0xFF,0x00,
	0x00,0x00,0x80,0xC0,0x60,0x18,0x06,0x01,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xE0,0x00,0x00,0x02,0x01,0x01,0x01,0x01,0x01,0x81,0xF9,0x0F,0x06,0x1C,
	0x30,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xC8,0xCC,0x64,0x22,0x13,0x11,0x13,0xE6,0xF8,0x88,0x8C,0x00,0x82,0x02,0x00,
	0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x80,0x85,0xFF,0xB4,0x64,0x00,0x01,0xC0,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0xFD,0x81,
	0x40,0x01,0x41,0x41,0xC1,0xF9,0x61,0x21,0x21,0x20,0x20,0x20,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x07,0x00,
	0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x07,0x04,0x04,0x08,0x08,0x08,0x08,0x08,0x08,
	0x08,0x06,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x07,0x00,0x00,0x00,0x00,
	0x00,0x00,0x01,0x03,0x06,0x04,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3E,0x44,0x82,0x83,0xC1,0x61,0x1C,0x07,0x00,0x00,0x01,0x01,0x00,0x00,
	0x00,0x00,0x04,0x0F,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x07,
	0x02,0x0E,0x18,0x10,0x20,0x40,0x7F,0x00,0x00,0x00,0xE0,0x80,0x70,0x1E,0x01,0x00,
	0x00,0x00,0x38,0x3C,0x03,0x01,0x03,0x04,0x08,0x10,0x30,0x30,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x00,
	0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x81,0x81,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1F,0xF0,0x8C,0x04,0x04,0x04,0xFF,0x04,0x00,0x04,0x04,0x84,0xC4,0x64,
	0x1C,0x0C,0xC0,0x80,0x40,0x42,0x01,0xC0,0xFE,0xC0,0x20,0x30,0x00,0x00,0x00,0xF0,
	0x00,0x80,0xA0,0x3C,0x00,0x80,0xC8,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xC0,0x20,0x00,0x00,0x60,0xE0,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,
	0xFF,0x80,0x41,0x62,0x4E,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
	0x00,0xF0,0x0F,0x01,0x0C,0x70,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0x40,
	0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0x01,0x01,0x00,0xF1,0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
	0x00,0x00,0x00,0x00,0x10,0x30,0x0C,0xFF,0x01,0x01,0x03,0x0E,0x04,0x03,0x00,0x83,
	0xFB,0x07,0x00,0x08,0x1A,0x33,0x60,0xC0,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,
	0x00,0x1F,0x04,0x00,0x00,0x80,0xF8,0x0F,0x01,0x03,0x06,0x0C,0x01,0xC1,0x79,0x07,
	0x01,0x02,0x04,0x08,0x18,0x30,0x20,0x60,0x40,0x80,0x80,0x00,0x00,0x00,0x00,0x00,
	0xF0,0x03,0x82,0x82,0x02,0x02,0x03,0xFE,0x02,0x00,0x01,0x01,0x00,0x38,0xE0,0x80,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x02,0x03,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char number[][64] = {
	
	{
		0x00,0xFE,0xFE,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0xFE,0xFE,0x00,
		0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
		0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
		0x00,0x7F,0x7F,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,
	},

	{
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x00,
	},

	{
		0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0xFE,0xFE,0x00,
		0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0x00,
		0x00,0xFF,0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
		0x00,0x7F,0x7F,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x00,
	},

	{
		0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0xFE,0xFE,0x00,
		0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0x00,
		0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF,0x00,
		0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,
	},

	{
		0x00,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0x00,
		0x00,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0x00,
		0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x00,
	},

	{
		0x00,0xFE,0xFE,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,
		0x00,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
		0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF,0x00,
		0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,
	},

	{
		0x00,0xFE,0xFE,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,
		0x00,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
		0x00,0xFF,0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF,0x00,
		0x00,0x7F,0x7F,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,
	},

	{
		0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0xFE,0xFE,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x00,
	},

	{
		0x00,0xFE,0xFE,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0xFE,0xFE,0x00,
		0x00,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0x00,
		0x00,0xFF,0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF,0x00,
		0x00,0x7F,0x7F,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,
	},

	{
		0x00,0xFE,0xFE,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0xFE,0xFE,0x00,
		0x00,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0x00,
		0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF,0x00,
		0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,
	}
};

// ��������
unsigned char bilibili[][32] = {
	
	{
		0x00,0xFC,0x04,0x04,0xFC,0x00,0x00,0xFF,0x88,0x48,0x00,0x7F,0x88,0x84,0xE2,0x00,
		0x00,0x0F,0x04,0x04,0x0F,0x00,0x04,0x05,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x00,/*"��",0*/
	},
	{
		0xFC,0x04,0x04,0xFC,0x00,0xFE,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0xFE,0x00,0x00,
		0x0F,0x04,0x04,0x0F,0x40,0x44,0x44,0x44,0x44,0x7F,0x44,0x44,0x44,0x44,0x40,0x00,/*"��",1*/
	},
	{
		0x00,0xFC,0x04,0x04,0xFC,0x00,0x00,0xFF,0x88,0x48,0x00,0x7F,0x88,0x84,0xE2,0x00,
		0x00,0x0F,0x04,0x04,0x0F,0x00,0x04,0x05,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x00,/*"��",2*/
	},
	{
		0xFC,0x04,0x04,0xFC,0x00,0xFE,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0xFE,0x00,0x00,
		0x0F,0x04,0x04,0x0F,0x40,0x44,0x44,0x44,0x44,0x7F,0x44,0x44,0x44,0x44,0x40,0x00,/*"��",3*/
	}
};

unsigned char Slogan[][32] = {
	
	{
		0x00,0x02,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x02,0x00,0x00,
		0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,/*"��",0*/
	},
	{
		0x00,0xFE,0x22,0xFE,0x00,0xFE,0x22,0xFE,0x00,0xFC,0x16,0x25,0x84,0xFC,0x00,0x00,
		0x60,0x1F,0x22,0xBF,0x40,0x3F,0x82,0xFF,0x00,0x13,0x12,0x12,0x52,0x82,0x7E,0x00,/*"��",1*/
	},
	{
		0x10,0x0C,0x24,0x24,0x24,0x24,0x25,0xE6,0x24,0x24,0x24,0x24,0x24,0x14,0x0C,0x00,
		0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,/*"��",2*/
	}
};

#endif	/* __BMP_H__ */
