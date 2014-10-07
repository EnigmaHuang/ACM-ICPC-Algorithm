Const
  MaxPoint = 200+1;
  MaxEdge  = 200*200+1;
  inf      = 'poj3687.txt';
  ouf      = 'poj3687ans.txt';
  Ondbg    = true;

Type
  TEdge = record
            target,nextpos:integer;
          end;

Var
  InPnt   : array[1..MaxPoint] of longint;
  Edges   : array[1..MaxEdge]  of TEdge;
  First	  : array[1..MaxPoint] of integer;
  Ans     : array[1..MaxPoint] of integer;
  Visited : array[1..MaxPoint] of boolean;

  n,m,EdgesNum,t,i:longint;

Procedure AddEdge(src,trg:longint);
begin
  inc(EdgesNum);
  inc(InPnt[trg]);
  with Edges[EdgesNum] do
  begin
    target:=trg;
    nextpos:=First[src];
  end;
  First[src]:=EdgesNum;
end;

Procedure ReadData;
var
  i,src,trg:longint;
begin
  readln(n,m);
  EdgesNum:=0;
  fillchar(InPnt,sizeof(InPnt),0);
  fillchar(First,sizeof(First),0);
  fillchar(Visited,sizeof(Visited),false);
  for i:=1 to m do
  begin
    readln(trg,src);    //注意是重的指向轻的，这样重的入度小先出队
    AddEdge(src,trg);
  end;
end;

Procedure TopSort;
var
  i,j,nowpos,sum:longint;
begin
  sum:=0;

  for i:=n downto 1 do    //直接扫描n次，统计有多少次出队列
  begin
    //从大的编号开始扫，确保大的编号先出队列
    for j:=n downto 1 do if (InPnt[j]=0) and (not Visited[j]) then
    begin
      ans[j]:=i;
      inc(sum);
      Visited[j]:=true;
      nowpos:=First[j];
      while nowpos<>0 do  //更新出队列的点连向的所有点的信息
      begin
        dec(InPnt[Edges[nowpos].target]);
        nowpos:=Edges[nowpos].nextpos;
      end;
      break;
    end;
  end;

  if sum <> n then
  begin
    writeln(-1);
    exit;
  end;
  for i:=1 to n do write(ans[i],' ');
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

  readln(t);
  for i:=1 to t do
  begin
    ReadData;
    TopSort;
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
