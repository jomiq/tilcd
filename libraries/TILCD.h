class TILCD
{
public:
	uint8_t _ce;
	uint8_t _di;
	uint8_t _wr;
	uint8_t _rst;

	uint8_t _d0;
	uint8_t _d1;
	uint8_t _d2;
	uint8_t _d3;
	uint8_t _d4;
	uint8_t _d5;
	uint8_t _d6;
	uint8_t _d7;

	uint8_t _contrast;
	TILCD(uint8_t ce, uint8_t di, uint8_t wr, uint8_t rst, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

	void init(uint8_t contrast);
	void reset();

	void setDisplayOn(bool on);
	void setCounterMode(bool y, bool up);
	void setContrast(uint8_t contrast);

	void setPos(uint8_t x, uint8_t y);
	void setX(uint8_t x);
	void setZ(uint8_t z);
	void setY(uint8_t y);

	void setScreenBytes(uint8_t bytes[]);

	void writeBinaryValue(uint8_t di, uint8_t value);
	
private:
	void setWordLength(bool eightBits);

};

TILCD::TILCD(uint8_t ce, uint8_t di, uint8_t wr, uint8_t rst, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
	_ce = ce;
	_di = di;
	_wr = wr;
	_rst = rst;

	_d0 = d0;
	_d1 = d1;
	_d2 = d2;
	_d3 = d3;
	_d4 = d4;
	_d5 = d5;
	_d6 = d6;
	_d7 = d7;

	_contrast = 48;

	pinMode(_d0, OUTPUT);
	pinMode(_d1, OUTPUT);
	pinMode(_d2, OUTPUT);
	pinMode(_d3, OUTPUT);
	pinMode(_d4, OUTPUT);
	pinMode(_d5, OUTPUT);
	pinMode(_d6, OUTPUT);
	pinMode(_d7, OUTPUT);

	pinMode(_ce, OUTPUT);
	pinMode(_di, OUTPUT);
	pinMode(_wr, OUTPUT);
	pinMode(_rst, OUTPUT);

	digitalWrite(_wr, LOW);
}

void TILCD::init(uint8_t contrast)
{
	_contrast = contrast;
	setWordLength(true);
	setCounterMode(false, true);
	setDisplayOn(true);
	setContrast(contrast);
	setPos(0, 0);
}

void TILCD::reset()
{
	digitalWrite(_rst, LOW);
	delay(200);
	digitalWrite(_rst, HIGH);
	init(_contrast);
}

void TILCD::setDisplayOn(bool on)
{
	writeBinaryValue(0, B00000010 | (on ? 1 : 0));
}

void TILCD::setCounterMode(bool y, bool up)
{
	writeBinaryValue(0, B00000100 | (y ? B10 : 0) | (up ? 1 : 0));
}

void TILCD::setContrast(uint8_t contrast)
{
	writeBinaryValue(0, B11000000 | (contrast & B00111111));
}

void TILCD::setPos(uint8_t x, uint8_t y)
{
	setX(x);
	setY(y);
}

void TILCD::setX(uint8_t x)
{
	writeBinaryValue(0, B00100000 | (x & B00011111));
}

void TILCD::setZ(uint8_t z)
{
	writeBinaryValue(0, B01000000 | (z & B00111111));
}

void TILCD::setY(uint8_t y)
{
	writeBinaryValue(0, B10000000 | (y & B00111111));
}

void TILCD::setScreenBytes(uint8_t bytes[])
{
	for (int x = 0; x < 12; x++)
	{
		setX(x);
		for (int y = 0; y < 64; y++)
		{
			writeBinaryValue(1, bytes[x * 64 + y]);
		}
	}
}

void TILCD::writeBinaryValue(uint8_t di, uint8_t value)
{
	digitalWrite(_ce, false);
	digitalWrite(_di, di);
	digitalWrite(_d0, HIGH && (value & B00000001));
	digitalWrite(_d1, HIGH && (value & B00000010));
	digitalWrite(_d2, HIGH && (value & B00000100));
	digitalWrite(_d3, HIGH && (value & B00001000));
	digitalWrite(_d4, HIGH && (value & B00010000));
	digitalWrite(_d5, HIGH && (value & B00100000));
	digitalWrite(_d6, HIGH && (value & B01000000));
	digitalWrite(_d7, HIGH && (value & B10000000));
	digitalWrite(_ce, true);
}

void TILCD::setWordLength(bool eightBits)
{
	writeBinaryValue(0, eightBits ? 1 : 0);
}