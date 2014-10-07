Const
  MaxPoint = 200+5;
  inf      = 'poj2570.txt';
  ouf      = 'poj2570ans.txt';
  Ondbg    = true;

Var
  M:array[1..MaxPoint,1..MaxPoint] of longint;{正常情况下是boolean}

  n:longint;

Procedure ReadData;
var
  i,a,b,pos:longint;
  Companys:string;
  c:char;
begin
  fillchar(M,SizeOf(M),0);

  read(a,b);
  while (a<>0) and (b<>0) do
  begin
    read(c);
    readln(Companys);
    for i:=1 to length(Companys) do
    begin
      pos:=ord(Companys[i])-ord('a');
      M[a,b]:=M[a,b]+(1 shl pos);       //公司编号为pos+1的位移为pos
    end;
    read(a,b);
  end;
  readln;
end;

Procedure Floyd;
var
  i,j,k:longint;
begin
  for k:=1 to n do       //枚举中继节点
    for i:=1 to n do     //枚举起始节点
      for j:=1 to n do   //枚举目标节点
        M[i,j]:=(M[i,k] and M[k,j]) or M[i,j];
end;

Procedure Solve;
var
  a,b,i:longint;
  ans:string;
begin
  Floyd;

  read(a,b);
  while (a<>0) and (b<>0) do
  begin
    ans:='';
    for i:=0 to 25 do
      if (M[a,b] and (1 shl i))>=1 then ans:=ans+chr(ord('a')+i);
    if ans='' then ans:='-';
    writeln(ans);
    read(a,b);
  end;

  writeln;
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  readln(n);
  while n<>0 do
  begin
    ReadData;
    Solve;
    readln(n);
  end;

  if Ondbg then
  begin
    Close(input);
    CLose(output);
  end;
End.
