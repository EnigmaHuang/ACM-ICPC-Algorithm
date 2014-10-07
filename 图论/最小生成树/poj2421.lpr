Const
  inf      = 'poj2421.txt';
  ouf      = 'poj2421ans.txt';
  PointNum = 100;
  EdgeNum  = PointNum*PointNum;
  Ondbg    = true;

Type
  TEdge = record
            src,trg,len:longint;
	  end;

Var
  Edges	:Array[1..EdgeNum] of TEdge;
  Father:Array[1..PointNum] of longint;

  n,m,q,ans:longint;

Procedure ReadData;
var
  i,j,tmp:longint;
begin
  read(n);
  m:=0;
  for i:=1 to n do
  begin
    for j:=1 to n do if i>j then //邻接矩阵，读右上半区即可
    begin
      inc(m);
      with Edges[m] do
      begin
        src:=i;
        trg:=j;
        read(len);
      end;
    end
    else read(tmp);
    readln;
  end;
  readln(q);
  for i:=1 to q do                //已经修筑好的路
  begin
    inc(m);
    with Edges[m] do
    begin
      readln(src,trg);
      len:=0;                     //边长为0，则一定会被选中
    end;
  end;
end;

Procedure QSort(l,r:longint);
var
  i,j,mid:longint;
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
  i,j:longint;
begin
  QSort(1,m);
  for i:=1 to n do Father[i]:=i;
  i:=1;
  j:=1;
  ans:=0;
  while i<=n-1 do          //注意，仍然只是n-1条边需要加入
  begin
    if Root(Edges[j].src)<>Root(Edges[j].trg) then
    begin
      Father[Root(Edges[j].src)]:=Root(Edges[j].trg);
      inc(i);
      ans:=ans+Edges[j].len;
    end;
    inc(j);
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
