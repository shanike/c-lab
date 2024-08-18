; my example!
macr my_fav_macro
cmpLabel: cmp     r3    ,       #-6   
bne          END 
endmacr
prn NAME
NAME: stop
;.data 1,,,  ,1,1,1,1      ,1,1,1,,,,1,1,1,1,1
.data 1,1   ,1,1, 1,1,
.string "some string"
.string
cmp r1 #4
my_fav_macro
END: stop
.entry NAME
.extern BLAH
.extern HHHI