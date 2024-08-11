; my example!
macr my_fav_macro
cmp r3, #-6 
bne          END 
endmacr
prt NAME
NAME:         .string		 "my name is a secret"
cmp @r1 #4
my_fav_macro
