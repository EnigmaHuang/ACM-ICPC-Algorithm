Const
  MaxPoint = 99;
  inf      = 'poj1975.txt';
  ouf      = 'poj1975ans.txt';
  Ondbg    = true;

Var
  f:array[1..MaxPoint,1..MaxPoint] of boolean;

  n,m,t,l:longint;

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
  i,j,Ans,Bigger,Smaller:longint;
begin
  Floyd;
  Ans:=0;

  for i:=1 to n do
  begin
    Bigger:=0;
    Smaller:=0;
    for j:=1 to n do
    begin
      if f[i,j] then inc(Bigger);
      if f[j,i] then inc(Smaller);
    end;
    if (Bigger>(n div 2)) or (Smaller>(n div 2)) then inc(Ans);
  end;

  writeln(Ans);
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  readln(t);
  for l:=1 to t do
  begin
    ReadData;
    Solve;
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
