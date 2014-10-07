Const
  MaxPoint = 120;
  MaxEdge  = 120*60;
  inf      = 'poj1422.txt';
  ouf      = 'poj1422ans.txt';
  Ondbg    = true;

Type
  TEdge = record
            target,nextpos:integer;
          end;

Var
  Edges:array[1..MaxEdge]  of TEdge;
  First:array[1..MaxPoint] of integer;
  EdgesNum:integer;

  Visited:array[1..MaxPoint] of boolean;
  LinkTo :array[1..MaxPoint] of integer;

  n,m,ans,testcase:integer;

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
  i,trg,src:integer;
begin
  fillchar(First,sizeof(First),0);
  EdgesNum:=0;

  readln(n,m);
  for i:=1 to m do
  begin
    readln(trg,src);
    AddEdge(trg,src);
  end;
end;

Function  FindMatch(src:integer):boolean;
var
  now,new,ptrpos:integer;
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
  i:integer;
begin
  ans:=0;
  Fillchar(LinkTo,SizeOf(LinkTo),0);

  for i:=1 to n do
  begin
    Fillchar(Visited,SizeOf(Visited),false);
    if FindMatch(i) then inc(ans);
  end;
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
  while (testcase>0) do
  begin
    ReadData;
    Hungary;
    writeln(n-ans);
    dec(testcase);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
