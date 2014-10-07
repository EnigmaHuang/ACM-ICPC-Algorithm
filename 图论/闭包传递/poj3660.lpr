Const
  MaxPoint = 100;
  inf      = 'poj3660.txt';
  ouf      = 'poj3660ans.txt';
  Ondbg    = true;

Var
  f:array[1..MaxPoint,1..MaxPoint] of boolean;

  n,m:longint;

Procedure ReadData;
var
  i,a,b:longint;
begin
  fillchar(f,SizeOf(f),false);

  readln(n,m);
  for i:=1 to m do
  begin
    readln(a,b);
    f[a,b]:=true;
  end;
end;

Procedure Floyd;
var
  i,j,k:longint;
begin
  for k:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        f[i,j]:=(f[i,k] and f[k,j]) or f[i,j];
end;

Procedure Solve;
var
  i,j,Ans,Counter:longint;
begin
  Floyd;
  Ans:=0;

  for i:=1 to n do
  begin
    Counter:=0;
    for j:=1 to n do if (f[i,j] or f[j,i]) then inc(Counter); //确定了i比j厉害或者j比i厉害
    if Counter=n-1 then inc(Ans);   //i对其他的n-1个的比较关系都确定了，则绝对排位确定
  end;

  write(Ans);
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  ReadData;
  Solve;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
