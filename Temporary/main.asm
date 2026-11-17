	include main.inc
	.code
		main PROC SYSTEMV
		invoke 	printf, "Hello World.."
		xor rax,rax
		ret
	main ENDP
	end