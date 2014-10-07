Const
  MaxPoint = 500;
  MaxEdge  = MaxPoint*MaxPoint;
  inf      = 'poj2594.txt';
  ouf      = 'poj2594ans.txt';
  Ondbg    = true;

Type
  TEdge = record
            target,nextpos:integer;
          end;

Var
  //Edges:array[1..MaxEdge]  of TEdge;
  //First:array[1..MaxPoint] of integer;
  //EdgesNum:integer;

  map:array[1..MaxPoint,1..MaxPoint] of boolean;

  Visited:array[1..MaxPoint] of boolean;
  LinkTo :array[1..MaxPoint] of integer;

  n,m,ans:integer;

{
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
}

Procedure ReadData;
var
  i,j,k,trg,src:integer;
begin
  //fillchar(First,sizeof(First),0);
  fillchar(map,sizeof(map),false);
  //EdgesNum:=0;

  for i:=1 to m do
  begin
    readln(src,trg);
    //AddEdge(src,trg);
    map[src,trg]:=true;
  end;

  for k:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        if map[i,k] and map[k,j] then
        begin
          //if map[i,j]=false then AddEdge(i,j);
          map[i,j]:=true;
        end;
end;

Function  FindMatch(src:integer):boolean;
var
  i,j:integer;
begin
  for i:=1 to n do
  begin
    if (Visited[i]=false) and map[src,i] then
    begin
      Visited[i]:=true;
      if (LinkTo[i]=0) or (FindMatch(LinkTo[i])) then
      begin
        LinkTo[i]:=src;
        exit(true);
      end;
    end;
  end;
  exit(false);
  {
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
  }
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

  readln(n,m);
  while not((n=0) and (m=0)) do
  begin
    ReadData;
    Hungary;
    writeln(n-ans);
    readln(n,m);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
