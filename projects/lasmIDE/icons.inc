.DATA

	Icons_ASM_PixBuf	gpointer	0
	Icons_INC_PixBuf	gpointer	0
	Icons_C_PixBuf		gpointer	0
	Icons_H_PixBuf		gpointer	0
	Icons_XML_PixBuf	gpointer	0
	Icons_WIDG_PixBuf	gpointer	0
	Icons_TXT_PixBuf	gpointer	0
	Icons_RC_PixBuf		gpointer	0
	Icons_ANY_PixBuf	gpointer	0
	Icons_FLDRO_PixBuf	gpointer	0
	Icons_FLDRC_PixBuf	gpointer	0
	Icons_PRJ_PixBuf	gpointer	0
	
.CODE	
	Icons_Init PROC
 		.if		Settings_Icons_ASM==0
 			mov Icons_ASM_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr asmfileicon	,asmfileiconSZ)
		.else
			mov Icons_ASM_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_ASM)
		.endif
 		.if		Settings_Icons_INC==0
 			mov Icons_INC_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr incfileicon	,incfileiconSZ)
		.else
			mov Icons_INC_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_INC)
		.endif
 		.if		Settings_Icons_C==0
			mov Icons_C_PixBuf		,rv(Helpers_Load_Pixbuf_From_Data,addr cfileicon	,cfileiconSZ)
		.else
			mov Icons_C_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_C)
 		.endif
 		.if		Settings_Icons_H==0
 			mov Icons_H_PixBuf		,rv(Helpers_Load_Pixbuf_From_Data,addr hfileicon	,hfileiconSZ)
		.else			
			xor rax,rax
			mov Icons_H_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_H)
		.endif
 		.if		Settings_Icons_XML==0
			mov Icons_XML_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr xmlfileicon	,xmlfileiconSZ)
		.else
			mov Icons_XML_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_XML)
 		.endif
 		.if		Settings_Icons_TXT==0
 			mov Icons_TXT_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr txtfileicon	,txtfileiconSZ)
		.else
			mov Icons_TXT_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_TXT)
		.endif
 		.if		Settings_Icons_RC==0
			mov Icons_RC_PixBuf		,rv(Helpers_Load_Pixbuf_From_Data,addr rcfileicon	,rcfileiconSZ)
		.else
			mov Icons_RC_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_RC)
 		.endif
 		.if		Settings_Icons_ANY==0
 			mov Icons_ANY_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr afileicon	,afileiconSZ)
		.else
			mov Icons_ANY_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_ANY)
		.endif
 		.if		Settings_Icons_WIDG==0
			mov Icons_WIDG_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr widgateicon	,widgateiconSZ)
		.else
			mov Icons_WIDG_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_WIDG)
 		.endif
 		.if		Settings_Icons_FLDRO==0
			mov Icons_FLDRO_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr folderopenedicon	,folderopenediconSZ)
		.else
			mov Icons_FLDRO_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_FLDRO)
 		.endif
 		.if		Settings_Icons_FLDRC==0
			mov Icons_FLDRC_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr folderclosedicon	,folderclosediconSZ)
		.else
			mov Icons_FLDRC_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_FLDRC)
 		.endif
 		.if		Settings_Icons_PRJ==0
			mov Icons_PRJ_PixBuf	,rv(Helpers_Load_Pixbuf_From_Data,addr projecticon	,projecticonSZ)
		.else
			mov Icons_PRJ_PixBuf,rv(Helpers_Load_Pixbuf_From_File,Settings_Icons_PRJ)
 		.endif


		ret
	Icons_Init ENDP
	  
    ;asm extention
    asmfileicon       DB	089h,050h,04eh,047h,00dh,00ah,01ah,00ah,000h,000h,000h,00dh,049h,048h,044h,052h
				DB	000h,000h,000h,020h,000h,000h,000h,020h,008h,006h,000h,000h,000h,073h,07ah,07ah
				DB	0f4h,000h,000h,000h,009h,070h,048h,059h,073h,000h,000h,00bh,013h,000h,000h,00bh
				DB	013h,001h,000h,09ah,09ch,018h,000h,000h,000h,0aah,049h,044h,041h,054h,058h,0c3h
				DB	0edh,096h,04bh,012h,080h,030h,008h,043h,089h,0e3h,0fdh,0afh,01ch,017h,06eh,0d4h
				DB	0e9h,007h,06dh,04bh,0eah,028h,04bh,036h,03ch,021h,069h,084h,0edh,045h,08bh,02bh
				DB	0a4h,09ah,051h,000h,0bch,0ceh,05ah,02ch,0beh,070h,084h,050h,000h,09ch,020h,056h
				DB	0c1h,0f0h,0e3h,009h,088h,08ah,016h,0e0h,0d0h,00bh,02ah,05ah,0c2h,0a5h,00fh,0b5h
				DB	006h,02ch,007h,040h,0c7h,0d7h,0b2h,071h,0e5h,036h,083h,00bh,02ch,0e7h,002h,028h
				DB	048h,056h,087h,0a0h,098h,080h,083h,0c3h,066h,096h,010h,01fh,04bh,01ah,090h,08bh
				DB	050h,092h,003h,04bh,087h,0c7h,0a4h,09bh,006h,0f8h,010h,002h,06fh,03ah,081h,01bh
				DB	000h,085h,03eh,07ah,09eh,063h,0cah,00dh,0e0h,089h,09ah,05bh,001h,0a8h,0deh,000h
				DB	0a2h,0edh,097h,07bh,08ah,03dh,043h,018h,0e1h,082h,0e6h,0bfh,0dch,011h,000h,01ch
				DB	001h,079h,027h,08eh,087h,0c6h,0b5h,0cah,005h,0fch,05ch,01ch,0ffh,000h,0f3h,001h
				DB	040h,09dh,005h,01bh,093h,0c5h,022h,039h,00dh,034h,0d3h,01bh,000h,000h,000h,000h
				DB	049h,045h,04eh,044h,0aeh,042h,060h,082h
    asmfileiconSZ        Dq  $-asmfileicon
    ;inc extention
    incfileicon          DB	089h,050h,04eh,047h,00dh,00ah,01ah,00ah,000h,000h,000h,00dh,049h,048h,044h,052h
			DB	000h,000h,000h,020h,000h,000h,000h,020h,008h,006h,000h,000h,000h,073h,07ah,07ah
			DB	0f4h,000h,000h,000h,009h,070h,048h,059h,073h,000h,000h,00bh,013h,000h,000h,00bh
			DB	013h,001h,000h,09ah,09ch,018h,000h,000h,000h,09fh,049h,044h,041h,054h,058h,0c3h
			DB	0edh,096h,0c1h,012h,080h,020h,008h,044h,059h,087h,0ffh,0ffh,0e5h,0edh,0d6h,0c1h
			DB	0a8h,0d1h,044h,068h,04ch,08eh,076h,0f0h,089h,08fh,04dh,088h,008h,025h,0aeh,060h
			DB	02dh,046h,001h,0d0h,0dah,0abh,048h,06ch,0a1h,086h,088h,006h,0b8h,040h,0e8h,0cdh
			DB	035h,020h,008h,002h,01ah,07ch,0fah,0fah,0a0h,044h,052h,007h,04eh,080h,062h,06ch
			DB	008h,0f9h,051h,0b1h,064h,013h,0c0h,090h,004h,09dh,061h,085h,017h,0f2h,0c1h,0cah
			DB	001h,03ah,099h,0ddh,0f2h,09dh,035h,000h,09fh,046h,0c5h,071h,0ech,064h,056h,014h
			DB	0f3h,0edh,03fh,046h,007h,0bch,061h,027h,010h,03ch,03ah,000h,027h,0d9h,05dh,0aeh
			DB	0c0h,025h,0b0h,04ah,0c2h,0a8h,0a7h,0beh,007h,036h,040h,00ah,000h,03fh,0ddh,001h
			DB	09dh,068h,03eh,05bh,082h,069h,069h,007h,0d0h,0e2h,0c6h,0ech,00eh,060h,0d8h,0d2h
			DB	0e5h,09fh,064h,01bh,000h,0c9h,00eh,0c8h,001h,0d5h,095h,023h,032h,084h,0e7h,070h
			DB	023h,000h,000h,000h,000h,049h,045h,04eh,044h,0aeh,042h,060h,082h 
    incfileiconSZ        DQ  $-incfileicon
    ;rc extention
    rcfileicon           DB  0
    rcfileiconSZ         DQ  $-rcfileicon
    ;c extention
    cfileicon            DB  0
    cfileiconSZ          DQ  $-cfileicon
    ;h extention
    hfileicon            DB  0
    hfileiconSZ          DQ  $-hfileicon
    ;text extention
    txtfileicon          DB  0
    txtfileiconSZ        DQ  $-txtfileicon
    ;Any extention
    xmlfileicon          DB  0
    xmlfileiconSZ        DQ  $-xmlfileicon
    ;Any extention
    afileicon            DB  0
    afileiconSZ          DQ  $-afileicon
    ;folder open extention
    folderopenedicon    	DB	089h,050h,04eh,047h,00dh,00ah,01ah,00ah,000h,000h,000h,00dh,049h,048h,044h,052h
			DB	000h,000h,000h,020h,000h,000h,000h,020h,008h,006h,000h,000h,000h,073h,07ah,07ah
			DB	0f4h,000h,000h,000h,009h,070h,048h,059h,073h,000h,000h,00bh,013h,000h,000h,00bh
			DB	013h,001h,000h,09ah,09ch,018h,000h,000h,000h,0a2h,049h,044h,041h,054h,058h,0c3h
			DB	0edh,057h,041h,00eh,0c0h,020h,008h,003h,0e2h,0ffh,0bfh,0dch,09dh,0b6h,018h,0e3h
			DB	026h,088h,086h,038h,0f5h,0b6h,003h,0a3h,094h,016h,091h,001h,080h,002h,08fh,050h
			DB	0f0h,039h,000h,052h,0feh,0c1h,0cch,0aah,0a0h,091h,0b2h,011h,04bh,0f2h,03bh,0b1h
			DB	016h,0a8h,099h,001h,04dh,075h,000h,088h,099h,01fh,010h,05eh,036h,0bah,034h,030h
			DB	0b2h,005h,0a9h,037h,0b0h,064h,0a2h,017h,0b0h,0cbh,005h,05ah,026h,0beh,040h,026h
			DB	02fh,085h,02dh,010h,02dh,086h,0ceh,020h,032h,0b5h,0c0h,0e3h,0ffh,05ah,02ch,080h
			DB	085h,05ah,030h,072h,0fah,0adh,027h,0c2h,019h,0d5h,0dfh,0f6h,0ddh,0d3h,086h,0f9h
			DB	0f0h,092h,028h,0f1h,085h,031h,050h,08eh,06eh,089h,0ach,07eh,03fh,011h,0d6h,06eh
			DB	04eh,089h,0a4h,09fh,088h,088h,0f3h,097h,0d1h,0cch,0a4h,06fh,07bh,083h,0cch,0dah
			DB	0f5h,0b4h,0ffh,035h,06fh,0c5h,0c7h,005h,0bfh,003h,070h,001h,0ddh,0eah,041h,03dh
			DB	074h,0c1h,09bh,0a9h,000h,000h,000h,000h,049h,045h,04eh,044h,0aeh,042h,060h,082h
    folderopenediconSZ   DQ  $-folderopenedicon
    ;folder closed extention
        	DB	089h,050h,04eh,047h,00dh,00ah,01ah,00ah,000h,000h,000h,00dh,049h,048h,044h,052h
			DB	000h,000h,000h,020h,000h,000h,000h,020h,008h,006h,000h,000h,000h,073h,07ah,07ah
			DB	0f4h,000h,000h,000h,009h,070h,048h,059h,073h,000h,000h,00bh,013h,000h,000h,00bh
			DB	013h,001h,000h,09ah,09ch,018h,000h,000h,000h,08dh,049h,044h,041h,054h,058h,0c3h
			DB	0edh,097h,04bh,00eh,0c0h,020h,008h,044h,01dh,0c2h,0fdh,0afh,04ch,057h,06dh,08ch
			DB	069h,015h,0fch,0d4h,0a6h,019h,076h,02eh,080h,0e7h,088h,082h,030h,033h,04bh,01bh
			DB	04dh,0d2h,066h,023h,080h,0e6h,00bh,000h,02eh,0a7h,099h,065h,023h,091h,0e4h,067h
			DB	062h,02fh,068h,058h,001h,0cfh,0eeh,0cch,02ch,001h,0b8h,020h,046h,0d5h,0e8h,0aah
			DB	081h,099h,047h,0a0h,0bdh,08eh,0a5h,012h,0bdh,0c0h,043h,0b7h,0c0h,0abh,044h,00dh
			DB	052h,047h,025h,06ch,041h,0b4h,014h,0fah,0d6h,03bh,010h,0a5h,08fh,018h,080h,05bh
			DB	0b5h,0e4h,08dh,0e4h,0b5h,098h,0ech,005h,004h,020h,000h,001h,008h,040h,000h,0e4h
			DB	03fh,0a3h,015h,00dh,0a8h,035h,03bh,0c8h,0aah,059h,0afh,08ch,0fbh,014h,03bh,03ch
			DB	015h,0b3h,008h,07fh,007h,070h,000h,051h,011h,038h,03dh,044h,022h,02ah,0b6h,000h
			DB	000h,000h,000h,049h,045h,04eh,044h,0aeh,042h,060h,082h
                         
    folderclosedicon     DB	089h,050h,04eh,047h,00dh,00ah,01ah,00ah,000h,000h,000h,00dh,049h,048h,044h,052h
			DB	000h,000h,000h,020h,000h,000h,000h,020h,008h,006h,000h,000h,000h,073h,07ah,07ah
			DB	0f4h,000h,000h,000h,009h,070h,048h,059h,073h,000h,000h,00bh,013h,000h,000h,00bh
			DB	013h,001h,000h,09ah,09ch,018h,000h,000h,000h,0b0h,049h,044h,041h,054h,058h,0c3h
			DB	0edh,097h,031h,00eh,080h,020h,00ch,045h,08bh,021h,070h,00ah,017h,056h,017h,06fh
			DB	0e0h,0e2h,0b1h,05dh,0bch,081h,08bh,06bh,017h,04eh,021h,00bh,04eh,026h,0c4h,028h
			DB	034h,002h,0d1h,0c4h,076h,063h,028h,0ffh,0e5h,0b7h,0d0h,054h,078h,0efh,03dh,0bch
			DB	018h,00dh,0bch,01ch,00ch,020h,0c3h,003h,05ah,04dh,04ah,032h,0edh,056h,0deh,081h
			DB	065h,055h,064h,061h,02ah,028h,025h,0c4h,0f1h,00ah,00eh,080h,0beh,073h,0c9h,0a4h
			DB	010h,020h,0d7h,08dh,047h,03dh,050h,0b2h,004h,0f2h,069h,0a2h,069h,037h,040h,0abh
			DB	049h,0e5h,088h,001h,067h,0bdh,002h,0aah,013h,031h,048h,099h,06bh,061h,00ah,022h
			DB	0e5h,0d0h,0b7h,0feh,081h,073h,04ch,0b3h,02ah,026h,084h,0a8h,060h,01ch,01ch,0ddh
			DB	081h,092h,0e2h,0b1h,03bh,079h,016h,030h,000h,003h,030h,000h,003h,030h,080h,008h
			DB	037h,023h,0b4h,01ah,010h,0ebh,02dh,04ah,057h,0d3h,050h,09ch,057h,0b3h,01ah,053h
			DB	0f0h,04ah,0f8h,016h,080h,09bh,0f0h,077h,000h,03bh,01eh,05bh,03fh,0dbh,0d0h,0d1h
			DB	001h,0cbh,000h,000h,000h,000h,049h,045h,04eh,044h,0aeh,042h,060h,082h
    folderclosediconSZ   DQ  $-folderclosedicon
    ;project extention	
    projecticon          DB	089h,050h,04eh,047h,00dh,00ah,01ah,00ah,000h,000h,000h,00dh,049h,048h,044h,052h
			DB	000h,000h,000h,020h,000h,000h,000h,020h,008h,006h,000h,000h,000h,073h,07ah,07ah
			DB	0f4h,000h,000h,000h,009h,070h,048h,059h,073h,000h,000h,00bh,013h,000h,000h,00bh
			DB	013h,001h,000h,09ah,09ch,018h,000h,000h,000h,0d2h,049h,044h,041h,054h,058h,0c3h
			DB	0edh,057h,0cbh,00eh,0c4h,020h,008h,02ch,084h,0ffh,0ffh,065h,0f6h,064h,0d2h,0b4h
			DB	088h,040h,087h,0bah,0c9h,0aeh,047h,06bh,019h,018h,01eh,0a3h,0a4h,0aah,07ah,06ch
			DB	05ch,07ch,06ch,05eh,0e2h,07dh,024h,022h,008h,088h,047h,032h,077h,081h,09fh,041h
			DB	03dh,05bh,0f2h,0c4h,0fbh,0c8h,0bfh,0abh,040h,024h,062h,0a8h,0cah,046h,0c4h,079h
			DB	041h,01bh,0cdh,03ah,0cbh,0e8h,088h,0a0h,05dh,050h,08dh,02eh,092h,07bh,0d8h,01ch
			DB	050h,0d5h,01bh,033h,099h,034h,070h,085h,0feh,001h,06ah,0a5h,024h,09bh,026h,0ceh
			DB	0d2h,03fh,003h,018h,0fbh,0d9h,022h,094h,09dh,005h,0b8h,064h,060h,080h,046h,0c1h
			DB	0b3h,0e7h,05bh,0c4h,028h,0ebh,084h,074h,0d0h,00ah,0ebh,002h,084h,01ah,0aeh,098h
			DB	068h,061h,020h,0aah,084h,07fh,031h,0fah,0feh,02bh,099h,025h,030h,091h,008h,05bh
			DB	0c4h,068h,066h,0d0h,04ah,049h,08bh,018h,0cdh,006h,0cdh,019h,0ach,032h,0aeh,0b9h
			DB	03ah,064h,0ach,028h,02bh,0ddh,0c2h,04fh,0abh,0ffh,0bah,00fh,095h,0e3h,0d9h,040h
			DB	0f1h,006h,08dh,0c5h,082h,0e7h,094h,0ach,02ah,019h,075h,0f1h,028h,0b7h,021h,0eah
			DB	075h,0f4h,0cah,020h,0aah,0b0h,042h,03fh,0ffh,03ah,0feh,000h,04ah,017h,08fh,024h
			DB	08ah,049h,05fh,078h,000h,000h,000h,000h,049h,045h,04eh,044h,0aeh,042h,060h,082h
    projecticonSZ        DQ  $-projecticon
    ;widgate extention
    widgateicon          DB	089h,050h,04eh,047h,00dh,00ah,01ah,00ah,000h,000h,000h,00dh,049h,048h,044h,052h
			DB	000h,000h,000h,020h,000h,000h,000h,020h,008h,006h,000h,000h,000h,073h,07ah,07ah
			DB	0f4h,000h,000h,000h,009h,070h,048h,059h,073h,000h,000h,00bh,013h,000h,000h,00bh
			DB	013h,001h,000h,09ah,09ch,018h,000h,000h,000h,0d6h,049h,044h,041h,054h,058h,0c3h
			DB	0edh,057h,0cbh,015h,004h,021h,008h,033h,0f3h,0e8h,0bfh,0e5h,06ch,003h,0a8h,07ch
			DB	0c2h,0cch,065h,03dh,0aah,040h,044h,013h,001h,0abh,03eh,078h,058h,043h,0d4h,009h
			DB	084h,081h,0e1h,0ach,041h,005h,080h,007h,05bh,03ah,0beh,0c2h,040h,090h,00ch,08ch
			DB	0c3h,01eh,054h,0ech,091h,03ch,0edh,04ah,002h,0d8h,0f9h,0c5h,00ah,0a4h,02dh,07ah
			DB	045h,06ch,05ch,027h,0ach,0f2h,070h,084h,083h,0f6h,066h,030h,06fh,0d2h,004h,029h
			DB	06dh,0b1h,0c7h,00eh,0b4h,0a2h,050h,02bh,0b6h,03eh,02ch,0c0h,06fh,016h,029h,01bh
			DB	002h,06fh,041h,091h,062h,032h,023h,0e1h,0ach,045h,01fh,021h,01ch,020h,00ah,059h
			DB	05fh,04fh,072h,03fh,0d4h,034h,07dh,09ah,0f6h,0f8h,01ah,0c0h,0fah,003h,0e8h,08eh
			DB	0aeh,014h,0f3h,0f6h,0dbh,04dh,000h,0e0h,045h,02fh,052h,02ah,06ah,08dh,0c0h,05eh
			DB	080h,0b4h,08ah,05ah,0f1h,0b4h,04ch,008h,0d7h,011h,088h,075h,03fh,093h,084h,04eh
			DB	0b8h,072h,06eh,043h,081h,0c3h,072h,06eh,043h,075h,0c0h,06bh,034h,06ch,0b3h,007h
			DB	0c5h,0f4h,0cbh,06ah,084h,06ah,059h,07eh,003h,020h,069h,04ch,0bah,0ddh,0d0h,078h
			DB	06bh,0b6h,0ebh,007h,047h,09bh,053h,00ah,07dh,0b5h,028h,047h,095h,056h,0fch,000h
			DB	065h,0bfh,040h,050h,0c9h,0a8h,0dah,073h,000h,000h,000h,000h,049h,045h,04eh,044h
			DB	0aeh,042h,060h,082h
    widgateiconSZ        DQ  $-widgateicon

