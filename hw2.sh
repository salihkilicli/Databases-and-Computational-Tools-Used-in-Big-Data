# Compiler Optimization Comparison - Intel vs GNU
# Runs a for loop for different options for each compiler and times the process

# Intel vs GNU Comparison with Options O0 (No optimization), O1 (Some for speed), O2 (All for speed), O3 (Aggressive), -fast

module load intel/2019

IC=("-O0" "-O1" "-O2" "-O3" "-fast")
GNU=("-O0" "-O1" "-O2" "-O3" "-Ofast")

echo "______________________________________________________________________"

echo "Comparing Intel Fortran vs GNU Fortran w/ different optimizers"

echo "______________________________________________________________________"


for i in {0..4}
	do
		ifort ${IC[$i]} -o brem brem.f gammln.f #Intel compiler
		echo "Time for" ${IC[$i]} "optimization of Intel compiler is"
		time ./brem < thik.inp $> /dev/null
		gfortran ${GNU[$i]} -o brem brem.f gammln.f #GNU compiler
		echo "Time for" ${GNU[$i]} "optimization of GNU compiler is"
		time ./brem < thik.inp $> /dev/null
done

echo "______________________________________________________________________"

echo "Comparing Intel compiler options along with -O2 (default) optimizer"

echo "______________________________________________________________________"


ICO=("-xHost" "-ipo" "-no-prec-div")

for j in {0..2}
	do
		ifort ${ICO[$j]} -o brem brem.f gammln.f #Intel compiler
		echo "Time for Intel compiler option" ${ICO[$j]} "along w/ -O2 is"
		time ./brem < thik.inp $> /dev/null
done

echo "______________________________________________________________________"

echo "Comparing GNU optimizer along with GNU vs Intel math library"

echo "______________________________________________________________________"

		gfortran -Ofast -o brem brem.f gammln.f 	  #GNU compiler
		echo "Time for -Ofast optimization of GNU w/ GNU math library is"
		time ./brem < thik.inp $> /dev/null
		gfortran -Ofast -o brem brem.f gammln.f -limf #GNU compiler with Intel math library
		echo "Time for -Ofast optimization of GNU w/ Intel math library is"
		time ./brem < thik.inp $> /dev/null

echo "______________________________________________________________________"





