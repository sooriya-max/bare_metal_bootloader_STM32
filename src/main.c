int x = 10, y; //x is for .data, y is for .bss
short z;       //z is added to check the size allocation for the int and short


int main()
{
    int z = x + y;
    return 0; // Dummy function that does nothing
}