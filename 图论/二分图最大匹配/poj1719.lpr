Const
  MaxPoint = 1000;
  MaxEdge  = MaxPoint*MaxPoint;
  inf      = 'poj1719.txt';
  ouf      = 'poj1719ans.txt';
  Ondbg    = true;

Type
  TEdge = record
            target,nextpos:longint;
          end;

Var
  Edges:array[1..MaxEdge]  of TEdge;
  First:array[1..MaxPoint] of longint;
  EdgesNum:longint;

  Visited:array[1..MaxPoint] of boolean;
  LinkTo :array[1..MaxPoint] of longint;

  r,c,testcase,ans:longint;
  Points:array[1..MaxPoint,1..2] of longint;

Procedure AddEdge(src,trg:longint);
begin
  inc(EdgesNum);
  with Edges[EdgesNum] do
  begin
    target:=trg;
    nextpos:=First[src];
  end;
  First[src]:=EdgesNum;
end;

Procedure ReadData;
var
  i,src1,src2:longint;
begin
  fillchar(First,sizeof(First),0);
  EdgesNum:=0;

  readln(r,c);
  for i:=1 to c do
  begin
    readln(src1,src2);
    AddEdge(src1,i);
    AddEdge(src2,i);
    Points[i,1]:=src1;
    Points[i,2]:=src2;
  end;
end;

Function  FindMatch(src:longint):boolean;
var
  now,new,ptrpos:longint;
begin
  now:=src;
  ptrpos:=First[now];
  FindMatch:=false;
  while ptrpos<>0 do
  begin
    new:=Edges[ptrpos].target;
    if not Visited[new] then
    begin
      Visited[new]:=true;
      if (LinkTo[new]=0) or (FindMatch(LinkTo[new])) then
      begin
        LinkTo[new]:=now;
        FindMatch:=true;
        exit;
      end;
    end;
    ptrpos:=Edges[ptrpos].nextpos;
  end;
end;

Procedure Hungary;
var
  i:longint;
begin
  ans:=0;
  Fillchar(LinkTo,SizeOf(LinkTo),0);

  for i:=1 to r do
  begin
    Fillchar(Visited,SizeOf(Visited),false);
    if FindMatch(i) then inc(ans);
  end;
end;

Procedure PrintAns;
var
  i:longint;
begin
  if ans<r then    //有行没有被匹配，则找不到合格的解
  begin
    writeln('NO');
    exit;
  end;
  for i:=1 to c do if LinkTo[i]=0 then LinkTo[i]:=Points[i,1];  //补齐未被匹配的列
  for i:=1 to c do write(LinkTo[i],' ');writeln;
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  readln(testcase);
  while testcase>0 do
  begin
    ReadData;
    Hungary;
    PrintAns;
    dec(testcase);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
