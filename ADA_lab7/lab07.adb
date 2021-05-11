--Author: Nicholas Jordan
--CMPS 3500 Lab07

--NOTICE: These procedures could easily be optimized but
--I wanted to try out some of Ada's different features

with Ada.Text_IO;
use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure lab07 is
	package Flt_IO is new Ada.Text_IO.Float_IO(FLOAT);
	use Flt_IO;

	-- value range constraint
	subtype Int is INTEGER range 0 .. 2048;

	-- index range constraint
	type Row is range 1 .. 3;
	type Col is range 1 .. 5;

	-- 2D array using range constraints
	type Matrix is array(Row, Col) of Int;
	
	-- declare 3 matrices
	mat1 : Matrix;
	mat2 : Matrix;
	result : Matrix;	

	--===========================================================================
	procedure FillMatrices(result1 : in out Matrix; result2 : in out Matrix) is 
		infile : FILE_TYPE;
		num : NATURAL;
	begin
		Open(infile, In_File, "lab07.in");
		-- fill first matrix
		for i in Row loop
			for j in Col loop
				Get(infile, num);
				result1(i, j) := num;
			end loop;
		end loop;
		-- fill second matrix
		for i in Row loop
			for j in Col loop
				Get(infile, num);
				result2(i, j) := num;
			end loop;
		end loop;
	end FillMatrices;
	--===========================================================================
	function MultiplyMatrices(mat1 : in Matrix; mat2 : in Matrix) return Matrix
	is
		result : Matrix;
	begin
		for i in Row loop
			for j in Col loop
				result(i, j) := mat1(i, j) * mat2(i, j);
			end loop;
		end loop;
		return result;
	end MultiplyMatrices;
	--===========================================================================
	procedure OutputResult(mat : in Matrix) is
		outfile : FILE_TYPE;
	begin
		Create(outfile, OUT_FILE, "lab07.out");
		
		for i in Row loop
			for j in Col loop
				-- format output by converting to string and concat space
				Put(outfile, (Integer'Image(mat(i,j)) & ','));	
			end loop;
		end loop;
	end OutputResult;
	--===========================================================================
	begin -- main lab07 procedure

	FillMatrices(mat1, mat2);

	result := MultiplyMatrices(mat1, mat2);

	OutputResult(result);

end lab07;
