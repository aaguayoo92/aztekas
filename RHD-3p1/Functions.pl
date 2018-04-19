#!/bin/perl

sub change 
{
  $a=$_[0];

$a=~s/([A-Za-z])\^(\d)/pow($1,$2.0)/g;
$a=~s/([A-Za-z])\^\((\d)\/(\d)\)/pow($1,$2.0\/$3.0)/g;
$a=~s/([A-Za-z])\^\((\d)(\d)\/(\d)\)/pow($1,$2$3.0\/$4.0)/g;
$a=~s/abs/fabs/g;
$a=~s/'diff\(([A-Z]),([a-z]),1\)/d$1$2/g;
$a=~s/r/x1/g;
$a=~s/z/x2/g;
$a=~s/theta/x3/g;
$a=~s/sqx1t/sqrt/g;
$a=~s/M/MM/g;
$a=~s/k/K/g;
return $a;
}

########################################################
##Headers##
########################################################

open(Matrix, ">../Headers/matrix.h");
print Matrix "double funct_A(double *a, double *uu);\n";
print Matrix "double funct_Dm(int i, double *uu);\n";
print Matrix "double funct_Dn(int i, double *uu);\n";
print Matrix "double funct_Do(int i, double *uu);\n";
close(Matrix);

open(Matrix, ">../Headers/vector.h");
print Matrix "double funct_Q(int i, double *uu);\n";
print Matrix "double funct_F(int i, double *uu);\n";
print Matrix "double funct_G(int i, double *uu);\n";
print Matrix "double funct_H(int i, double *uu);\n";
print Matrix "double funct_S(int i, double *uu);\n";
close(Matrix);

########################################################
##MATRIX A##
########################################################

open(Matrix, 'DIFF');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @b = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$b[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$b[$i-1] = change $b[$i-1];
}

open(Matrix, 'PARAM');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @c = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$c[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$c[$i-1] = change $c[$i-1];
}

open(Matrix, 'MATRIX_A');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">amatrix.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/matrix.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_A(double *a, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   int i, j;\n";
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   dWu = $b[0]";
print Matrix "   dWv = $b[1]";
print Matrix "   dWw = $b[2]";
print Matrix "   dOn = $b[3]";
print Matrix "   dOp = $b[4]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
print Matrix "   for(i = 0; i < eq; i++)\n";
print Matrix "   {\n";
print Matrix "      for(j = 0; j < eq; j++)\n";
print Matrix "      {\n";
foreach my $i (0..4){
	foreach my $j (0..4){   
		if($i == 0 && $j==0){
			print Matrix "         if(i == 0 && j == 0)\n";
			print Matrix "         {\n";
			print Matrix "            a[i*eq + j] = $a[$i*5 + $j]";     
			print Matrix "         }\n";
		}                       
		else{                   
			print Matrix "         else if(i == $i && j == $j)\n";
			print Matrix "         {\n";                                
			print Matrix "            a[i*eq + j] = $a[$i*5 + $j]";     
			print Matrix "         }\n";
		}
	}
}                                    
print Matrix "     \n";
print Matrix "      }\n";
print Matrix "     \n";
print Matrix "   }\n";
print Matrix "   return 0;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);

########################################################
##MATRIX Dm##
########################################################

open(Matrix, 'MATRIX_Dm');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">dmmatrix.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/matrix.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_Dm(int i, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   double a;\n";  
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   dWu = $b[0]";
print Matrix "   dWv = $b[1]";
print Matrix "   dWw = $b[2]";
print Matrix "   dOn = $b[3]";
print Matrix "   dOp = $b[4]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
foreach my $i (0..$#a-1){
	if($i == 0){
		print Matrix "   if(i == 0)\n";
		print Matrix "   {\n";
		print Matrix "      a = $a[$i]";
		print Matrix "   }\n";
	}  
	else{                                 
		print Matrix "   else if(i == $i)\n";
		print Matrix "   {\n";                                
		print Matrix "      a = $a[$i]";     
		print Matrix "   }\n";
	}
}
print Matrix "   return a;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);

########################################################
##MATRIX Dn##
########################################################

open(Matrix, 'MATRIX_Dn');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">dnmatrix.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/matrix.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_Dn(int i, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   double a;\n";  
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   dWu = $b[0]";
print Matrix "   dWv = $b[1]";
print Matrix "   dWw = $b[2]";
print Matrix "   dOn = $b[3]";
print Matrix "   dOp = $b[4]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
foreach my $i (0..$#a-1){
	if($i == 0){
		print Matrix "   if(i == 0)\n";
		print Matrix "   {\n";
		print Matrix "      a = $a[$i]";
		print Matrix "   }\n";
	}
	else{                                   
		print Matrix "   else if(i == $i)\n";
		print Matrix "   {\n";                                
		print Matrix "      a = $a[$i]";     
		print Matrix "   }\n";
	}
}
print Matrix "   return a;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);

########################################################
##MATRIX Do##
########################################################

open(Matrix, 'MATRIX_Do');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">domatrix.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/matrix.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_Do(int i, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   double a;\n";  
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   dWu = $b[0]";
print Matrix "   dWv = $b[1]";
print Matrix "   dWw = $b[2]";
print Matrix "   dOn = $b[3]";
print Matrix "   dOp = $b[4]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
foreach my $i (0..$#a-1){
	if($i == 0){
		print Matrix "   if(i == 0)";
		print Matrix "   {\n";
		print Matrix "      a = $a[$i]";
		print Matrix "   }\n";
	}
	else{                                   
		print Matrix "   else if(i == $i)\n";
		print Matrix "   {\n";                                
		print Matrix "      a = $a[$i]";     
		print Matrix "   }\n";
	}
}
print Matrix "   return a;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);

########################################################
##VECTOR Q##
########################################################

open(Matrix, 'VECTOR_Q');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">qvector.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/vector.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_Q(int i, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   double a;\n";  
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
foreach my $i (0..$#a-1){                                   
	if($i == 0){
		print Matrix "   if(i == 0)\n";
		print Matrix "   {\n";
		print Matrix "      a = $a[$i]";
		print Matrix "   }\n";
	}
	else{
		print Matrix "   else if(i == $i)\n";
		print Matrix "   {\n";                                
		print Matrix "      a = $a[$i]";     
		print Matrix "   }\n";
	}
}                                    
print Matrix "   return a;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);

########################################################
##VECTOR F##
########################################################

open(Matrix, 'VECTOR_F');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">fvector.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/vector.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_F(int i, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   double a;\n";  
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
foreach my $i (0..$#a-1){                                   
	if($i == 0){
		print Matrix "   if(i == 0)\n";
		print Matrix "   {\n";
		print Matrix "      a = $a[$i]";
		print Matrix "   }\n";
	}
	else{
		print Matrix "   else if(i == $i)\n";
		print Matrix "   {\n";                                
		print Matrix "      a = $a[$i]";     
		print Matrix "   }\n";
	}
}                                    
print Matrix "   return a;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);

########################################################
##VECTOR G##
########################################################

open(Matrix, 'VECTOR_G');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">gvector.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/vector.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_G(int i, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   double a;\n";  
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
foreach my $i (0..$#a-1){                                   
	if($i == 0){
		print Matrix "   if(i == 0)\n";
		print Matrix "   {\n";
		print Matrix "      a = $a[$i]";
		print Matrix "   }\n";
	}
	else{
		print Matrix "   else if(i == $i)\n";
		print Matrix "   {\n";                                
		print Matrix "      a = $a[$i]";     
		print Matrix "   }\n";
	}
}                                    
print Matrix "   return a;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);

########################################################
##VECTOR H##
########################################################

open(Matrix, 'VECTOR_H');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">hvector.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/vector.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_H(int i, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   double a;\n";  
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
foreach my $i (0..$#a-1){                                   
	if($i == 0){
		print Matrix "   if(i == 0)\n";
		print Matrix "   {\n";
		print Matrix "      a = $a[$i]";
		print Matrix "   }\n";
	}
	else{
		print Matrix "   else if(i == $i)\n";
		print Matrix "   {\n";                                
		print Matrix "      a = $a[$i]";     
		print Matrix "   }\n";
	}
}                                    
print Matrix "   return a;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);

########################################################
##VECTOR S##
########################################################

open(Matrix, 'VECTOR_S');
@lines = <Matrix>;
my $size = @lines;
my $s = $size - 1;
my @a = (0) x @lines;
#print @lines;

foreach my $i (1..$size){
	$a[$i-1] = $lines[$i];
}

foreach my $i (1..$size){
	$a[$i-1] = change $a[$i-1];
}

open(Matrix, ">svector.c");
print Matrix "#include<stdio.h>\n";
print Matrix "#include<math.h>\n";
print Matrix "#include\"../Headers/vector.h\"\n";
print Matrix "#include\"../Headers/main.h\"\n";
print Matrix "    \n";

print Matrix "double funct_S(int m, double *uu)\n";
print Matrix "{\n";                                                 
print Matrix "   double a;\n";  
print Matrix "   double n, p, u=0, v=0, w=0;\n";
print Matrix "   double r, W, O;\n";
print Matrix "   double dWu, dWv, dWw;\n";
print Matrix "   double dOn, dOp;\n";
print Matrix "   n = uu[0];\n";
print Matrix "   p = uu[1];\n";
print Matrix "   u = uu[2];\n";
print Matrix "   if(dim >= 2){v = uu[3];}\n";
print Matrix "   if(dim == 3){w = uu[4];}\n";
print Matrix "    \n";
print Matrix "   r = $c[0]";
print Matrix "   W = $c[1]";
print Matrix "   O = $c[2]";
print Matrix "    \n";
print Matrix "   if(W >= 1)\n";
print Matrix "   {\n";
print Matrix "   }\n";
print Matrix "   else\n";
print Matrix "   {\n";
print Matrix "      W = 10;\n";
print Matrix "   }\n";
print Matrix "    \n";
foreach my $i (0..$#a-1){                                   
	if($i == 0){
		print Matrix "   if(m == 0)\n";
		print Matrix "   {\n";
		print Matrix "      a = $a[$i]";
		print Matrix "   }\n";
	}
	else{
		print Matrix "   else if(m == $i)\n";
		print Matrix "   {\n";                                
		print Matrix "      a = $a[$i]";     
		print Matrix "   }\n";
	}
}                                    
print Matrix "   return a;\n";                                       
print Matrix "}\n";                                                 
close(Matrix);
