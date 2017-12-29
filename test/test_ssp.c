int main()
{
	char buffer[4];
	
	for (int i = 0; i <= 10; i++)
	{
		// When compiled with stack protector support, this line
		//   will print something to the effect of:
		//
		//   *** stack smashing detected ***: <unknown> terminated
		//   Aborted (core dumped)
		//
		//   when i == 10, because 10 is an out of bounds write.
		//   This will throw a SIGABRT, retruning code 134.

		buffer[i] = (char)i;
	}

	return 0;
}
