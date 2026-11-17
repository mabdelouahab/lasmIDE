	
.data
	TStr	dq	2048+2	dup (0);STDOUT
	PStr	dq	2048+2	dup (0);STDOUT
	QStr	dq	2048+2	dup (0);STDOUT

	_PStr	dq	2048+2	dup (0);STDOUT
	_QStr	dq	2048+2	dup (0);STDOUT
	addr_PStr	DQ	_PStr
	addr_QStr	DQ	_QStr

	.sub GetTowPrims,addr_P:QWORD,addr_Q:QWORD
		local a:qword
		.home
		invoke printf,"/*Generate tow prime numbers.../*\n"	 
		_getrandom(addr TStr,64,1)
		lea rax,TStr
		or  byte ptr [rax],129
		or  byte ptr [rax+128-1],129

		mov a,0
		@@:
			lea rax,TStr
			add rax,a
			xor r10,r10
			mov r10b,byte ptr [rax]
			mov rax,addr_PStr
			add rax,a
			add rax,a
			invoke sprintf,rax,"%02X"	,r10
			inc a
			cmp a,64
			jne @B
		mpz_init	(addr_P	)
		mpz_set_str(addr_P,addr_PStr,16);

		_getrandom(addr TStr,64,1)
		lea rax,TStr
		or  byte ptr [rax],129
		or  byte ptr [rax+128-1],129

		mov a,0
		@@:
			lea rax,TStr
			add rax,a
			xor r10,r10
			mov r10b,byte ptr [rax]
			mov rax,addr_QStr
			add rax,a
			add rax,a
			invoke sprintf,rax,"%02X"	,r10
			inc a
			cmp a,64
			jne @B
		mpz_init	(addr_Q	)
		mpz_set_str(addr_Q,addr_QStr,16);

		mpz_nextprime(addr_P,addr_P)
		mpz_nextprime(addr_Q,addr_Q)
		mp_printf("P=%#Zd \n",addr_P)
		mp_printf("Q=%#Zd\n",addr_Q)

	.endsub

	.sub GetTowPrimsEx,addr_P:QWORD,addr_Q:QWORD,pq_sz:QWORD
		local a:qword
		.home
		invoke printf,"/*Generate tow prime numbers.../*\n"	 
		_getrandom(addr TStr,pq_sz,1)
		lea rax,TStr
		mov rcx,pq_sz
		add rcx,pq_sz
		dec rcx
		add rcx,rax
		or  byte ptr [rax],129
		or  byte ptr [rcx],129

		mov a,0
		@@:
			lea rax,TStr
			add rax,a
			xor r10,r10
			mov r10b,byte ptr [rax]
			mov rax,addr_PStr
			add rax,a
			add rax,a
			invoke sprintf,rax,"%02X"	,r10
			inc a
			mov rax,pq_sz
			cmp a,rax
			jne @B
		mpz_init	(addr_P	)
		mpz_set_str(addr_P,addr_PStr,16);

		_getrandom(addr TStr,pq_sz,1)
		lea rax,TStr
		mov rcx,pq_sz
		add rcx,pq_sz
		dec rcx
		add rcx,rax
		or  byte ptr [rax],129
		or  byte ptr [rcx],129

		mov a,0
		@@:
			lea rax,TStr
			add rax,a
			xor r10,r10
			mov r10b,byte ptr [rax]
			mov rax,addr_QStr
			add rax,a
			add rax,a
			invoke sprintf,rax,"%02X"	,r10
			inc a
			mov rax,pq_sz
			cmp a,rax
			jne @B
		mpz_init	(addr_Q	)
		mpz_set_str(addr_Q,addr_QStr,16);

		mpz_nextprime(addr_P,addr_P)
		mpz_nextprime(addr_Q,addr_Q)
		mp_printf("P=%#Zd \n",addr_P);"P=%#ZX
		mp_printf("Q=%#Zd\n",addr_Q)

	.endsub
	.sub GetMulPQ,addr_D:QWORD,addr_P:QWORD,addr_Q:QWORD
		.home
		invoke printf,"/* Calculate D=P*Q... ...*/\n"	
		mpz_init(addr_D)
		mpz_mul(addr_D,addr_P,addr_Q);
		mp_printf("D=%#Zd\n",addr_D);D=%#ZX
	.endsub
	.sub mp_printf_bin,addr_D:QWORD
		local a
		.home
		mpz_sizeinbase	(addr_D,2)
		mov a,eax
		@@:
		dec a
		mpz_tstbit		(addr_D	,a)
		.if eax==0
			printf("0")
		.else
			printf("1")
		.endif
		.if a
			jmp @B
		.endif
	.endsub
.DATA
				DQ	3,5,7,11,13,65537,19,23,29,31,37,41,43,0
		DQ  2,3,5,7,11,13,17,19,23
				DQ  29,31,37,41,43,47,53,59,61
				DQ  67,71,73,79,83,89,97,101,103
				DQ  107,109,113,127,131,137,139,149,151
				DQ  157,163,167,173,179,181,191,193,197
				DQ  199,211,223,227,229,233,239,241,251
				DQ  257,263,269,271,277,281,283,293,307
				DQ  311,313,317,331,337,347,349,353,359
				DQ  367,373,379,383,389,397,401,409,419
				DQ  421,431,433,439,443,449,457,461,463
				DQ  467,479,487,491,499,503,509,521,523
				DQ  541,547,557,563,569,571,577,587,593	
			 DQ 2857,2861,2879,2887,2897,2903,2909,2917,2927
			 DQ 2939,2953,2957,2963,2969,2971,2999,3001,3011
			 DQ 3019,3023,3037,3041,3049,3061,3067,3079,3083
			 DQ 3089,3109,3119,3121,3137,3163,3167,3169,3181
			 DQ 3187,3191,3203,3209,3217,3221,3229,3251,3253
			 DQ 3257,3259,3271,3299,3301,3307,3313,3319,3323
			 DQ 3329,3331,3343,3347,3359,3361,3371,3373,3389
			 DQ 3391,3407,3413,3433,3449,3457,3461,3463,3467
			 DQ 3469,3491,3499,3511,3517,3527,3529,3533,3539
			DQ 10273,10289,10301,10303,10313,10321,10331,10333,10337
			DQ 10343,10357,10369,10391,10399,10427,10429,10433,10453
			DQ 10457,10459,10463,10477,10487,10499,10501,10513,10529
			DQ 10531,10559,10567,10589,10597,10601,10607,10613,10627
			DQ 10631,10639,10651,10657,10663,10667,10687,10691,10709
			DQ 10711,10723,10729,10733,10739,10753,10771,10781,10789
			DQ 10799,10831,10837,10847,10853,10859,10861,10867,10883
			DQ 10889,10891,10903,10909,10937,10939,10949,10957,10973
			DQ 10979,10987,10993,11003,11027,11047,11057,11059,11069
			DQ 11071,11083,11087,11093,11113,11117,11119,11131,11149
			DQ 11159,11161,11171,11173,11177,11197,11213,11239,11243
			DQ 11251,11257,11261,11273,11279,11287,11299,11311,11317
			DQ 11321,11329,11351,11353,11369,11383,11393,11399,11411
			DQ 11423,11437,11443,11447,11467,11471,11483,11489,11491
			DQ 11497,11503,11519,11527,11549,11551,11579,11587,11593
			DQ 11597,11617,11621,11633,11657,11677,11681,11689,11699
	PRIMS_ARRAY		DQ 11701,11717,11719,11731,11743,11777,11779,11783,11789
			DQ 11801,11807,11813,11821,11827,11831,11833,11839,11863
			DQ 11867,11887,11897,11903,11909,11923,11927,11933,11939
			DQ 11941,11953,11959,11969,11971,11981,11987,12007,12011
			DQ 12037,12041,12043,12049,12071,12073,12097,12101,12107
			DQ 12109,12113,12119,12143,12149,12157,12161,12163,12197

				