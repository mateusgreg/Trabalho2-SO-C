
int getMinimumInt(){
	int nMin = 8;
	int nWidth = 8;
	while(0 < (nMin <<= 4)) nWidth += 4;
	return nMin;
}

int getMaximumInt(){
	return getMinimumInt()^-1;
}

