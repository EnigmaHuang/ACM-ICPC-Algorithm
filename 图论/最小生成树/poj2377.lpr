Const
  inf      = 'poj2377.txt';
  ouf      = 'poj2377ans.txt';
  PointNum = 1000;
  EdgeNum  = 20000;
  Ondbg    = true;

Type
  TEdge = record
            src,trg,len:longint;
	  end;

Var
  Edges	:Array[1..EdgeNum] of TEdge;
  Father:Array[1..PointNum] of longint;

  n,m:longint;
  ans:int64;

Procedure ReadData;
var
  i:longint;
Begin
  read(n,m);
  for i:=1 to m do with Edges[i] do readln(src,trg,len);
End;

Procedure QSort(l,r:longint);
var
  i,j,mid:longint;
  swap:TEdge;
begin
  i:=l;j:=r;
  mid:=Edges[(i+j)div 2].len;
  while i<j do
  begin
    while Edges[i].len>mid do inc(i);  //要费用最大，降序
    while Edges[j].len<mid do dec(j);
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
  i,j:longint;
begin
  QSort(1,m);
  for i:=1 to n do Father[i]:=i;
  i:=1;
  j:=1;
  ans:=0;
  while i<=n-1 do
  begin
    if Root(Edges[j].src)<>Root(Edges[j].trg) then
    begin
      Father[Root(Edges[j].src)]:=Root(Edges[j].trg);
      inc(i);
      ans:=ans+Edges[j].len;
    end;
    inc(j);
    if (j=m) and (i<n) then
    begin
      ans:=-1;
      break; //有仓库无法被连接
    end;
  end;
end;

Procedure PrintAnswer;
begin
  writeln(ans);
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
