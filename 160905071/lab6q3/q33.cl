__kernel void rev_str(__global char *a,int l){
	int i=get_global_id(0);
	char temp;
	temp=a[i];
	a[i]=a[l-1-i];
	a[l-1-i]=temp;
}

