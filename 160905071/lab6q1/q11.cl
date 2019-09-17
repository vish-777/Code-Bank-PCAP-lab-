__kernel void ascii_rev(__global char *A){
	int i=get_global_id(0);
	char ch=A[i];
	int ascval=(int)ch;
	int rev=0;
	while(ascval>0){
		int rem=ascval%10;
		rev=rev*10+rem;
		ascval/=10;
	}
	A[i]=(char)rev;
}



