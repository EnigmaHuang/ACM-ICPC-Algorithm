Const
  MaxPoint = 100;
  MaxEdge  = MaxPoint*MaxPoint;
  inf      = 'poj2536.txt';
  ouf      = 'poj2536ans.txt';
  Ondbg    = true;

Type
  TEdge = record
            target,nextpos:integer;
          end;

  TCoordinate = record
                  x,y:double;
                end;

Var
  Edges:array[1..MaxEdge]  of TEdge;
  First:array[1..MaxPoint] of integer;
  EdgesNum:integer;

  Visited:array[1..MaxPoint] of boolean;
  LinkTo :array[1..MaxPoint] of integer;

  n,m,ans,si,vi:integer;
  s,v:double;

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
  i,j,k,trg:integer;
  gophers:array[1..MaxPoint] of TCoordinate;
  hole:TCoordinate;
  dist:double;
begin
  fillchar(First,sizeof(First),0);
  EdgesNum:=0;

  readln(n,m,si,vi);
  s:=si+0.0;
  v:=vi+0.0;
  for i:=1 to n do with gophers[i] do readln(x,y);
  for i:=1 to m do
  begin
    readln(hole.x,hole.y);
    for j:=1 to n do
    begin
      dist:=(gophers[j].x-hole.x)*(gophers[j].x-hole.x);
      dist:=dist+(gophers[j].y-hole.y)*(gophers[j].y-hole.y);
      dist:=sqrt(dist);
      if dist<=s*v then AddEdge(j,i);
    end;
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

  while not eof(input) do
  begin
    ReadData;
    Hungary;
    writeln(n-ans);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
