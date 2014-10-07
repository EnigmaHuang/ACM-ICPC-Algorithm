Const
  inf      = 'poj3625.txt';
  ouf      = 'poj3625ans.txt';
  PointNum = 1000;
  EdgeNum  = 999*999;
  Ondbg    = true;

Type
  TEdge = record
            src,trg:longint;
            len:double;
	  end;

  TPosi = record
            x,y:double;
          end;

Var
  Edges	:array[1..EdgeNum]  of TEdge;
  Father:array[1..PointNum] of longint;

  Pos   :array[1..PointNum] of TPosi;

  n,m:longint;
  ans:double;

Procedure ReadData;
var
  i,j:longint;
  dx,dy:double;
begin
  read(n,m);
  for i:=1 to n do with Pos[i] do readln(x,y);

  for i:=1 to m do with Edges[i] do   //已经修好的路
  begin
    readln(src,trg);
    len:=0;
  end;

  for i:=2 to n do
    for j:=1 to i-1 do
    begin
      inc(m);
      Edges[m].src:=i;
      Edges[m].trg:=j;
      dx:=(pos[i].x-pos[j].x);
      dy:=(pos[i].y-pos[j].y);
      Edges[m].len:=sqrt(dx*dx+dy*dy);
    end;
end;

Procedure QSort(l,r:longint);
var
  i,j:longint;
  mid:double;
  swap:TEdge;
begin
  i:=l;j:=r;
  mid:=Edges[(i+j)div 2].len;
  while i<j do
  begin
    while Edges[i].len<mid do inc(i);
    while Edges[j].len>mid do dec(j);
    if i<=j then
    begin
      swap:=Edges[i];
      Edges[i]:=Edges[j];
      Edges[j]:=swap;
      inc(i);dec(j);
    end;
  end;
 if i<r then QSort(i,r);
 if l<j then QSort(l,j);
end;

Function Root(v:longint):Longint;
begin
  if Father[v]=v then Root:=v
  else
  begin
    Father[v]:=Root(Father[v]);
    Root:=Father[v];
  end;
end;

Procedure Kruskal;
Var
  i,j,RS,RT:longint;
begin
  QSort(1,m);
  for i:=1 to n do Father[i]:=i;
  i:=1;
  j:=1;
  ans:=0;
  while i<=n-1 do
  begin
    RS:=Root(Edges[j].src);
	RT:=Root(Edges[j].trg);
    if RS<>RT then
    begin
      Father[RS]:=RT;
      inc(i);
      ans:=ans+Edges[j].len;
    end;
    inc(j);
  end;
end;

Procedure PrintAnswer;
begin
  writeln(ans:0:2);
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
  Kruskal;
  PrintAnswer;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
