Const
  MaxNode = 20;
  inf     = 'poj1300.txt';
  ouf     = 'poj1300ans.txt';
  Ondbg   = true;


Var
  d:array[0..MaxNode] of integer;      //入度
  NodeNum,EdgeNum,start:integer;
  tmp:string[6];

Procedure ReadData;
var
  i,j,t:integer;
  code:word;
  s,s2:string;
begin
  fillchar(d,sizeof(d),0);
  EdgeNum:=0;

  readln(start,NodeNum);
  for i:=0 to NodeNum-1 do
  begin
    readln(s);
    if length(s)=0 then continue;
    repeat
      for j:=1 to length(s) do if s[j]=' ' then break;
      if j=length(s) then inc(j);
      s2:=copy(s,1,j-1);
      val(s2,t,code);
      delete(s,1,j-1);
      if j<>length(s2) then delete(s,1,1);
      inc(d[i]);
      inc(d[t]);
      inc(EdgeNum);
    until length(s)=0;
  end;
  readln(s);
end;

Procedure Solve;
var
  i,even,od:integer;
begin
  even:=0;
  od:=0;
  for i:=0 to NodeNum-1 do if Odd(d[i]) then inc(od) else inc(even);
  if (od=0) and (start=0) then writeln('YES ',EdgeNum)
  else if (od=2) and Odd(d[start]) and Odd(d[0]) and (start<>0) then writeln('YES ',EdgeNum)
  else writeln('NO');
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);Reset(input);
    Assign(output,ouf);Rewrite(output);
  end;

  read(tmp);
  while tmp<>'ENDOFI' do
  begin
    ReadData;
    Solve;
    read(tmp);
  end;

  if Ondbg then
  begin
    Close(input);Close(output);
  end;
End.
