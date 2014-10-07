Program TopSortExample;

Const
  MaxPoint = 100;
  MaxEdge  = 1000;
  QueueLen = 1000;
  inf      = 'TopSortExample.txt';
  ouf      = 'TopSortExampleAns.txt';

Type
  TEdge = record
            target,nextpos:longint;
          end;

Var
  Edges:array[1..MaxEdge]  of TEdge;     //边数组，模拟邻接表
  First:array[1..MaxEdge]  of longint;   //从该顶点出发的边在数组中的最后位置
  Queue:array[1..QueueLen] of longint;   //队列堆栈记录优化
  InPnt:array[1..MaxPoint] of longint;   //各点的入度数

  n,m,EdgesNum:longint;
  head,tail:longint;

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
  Fillchar(First,SizeOf(First),0);
  Fillchar(InPnt,SizeOf(InPnt),0);
  EdgesNum:=0;

  readln(n,m);
  for i:=1 to m do
  begin
    readln(src,trg);
    AddEdge(src,trg);
  end;
end;

Procedure QueueOut(var pnt:longint);
begin
  inc(head);
  if head>QueueLen then head:=head-QueueLen;
  pnt:=Queue[head];
end;

Procedure QueueIn(pnt:longint);
begin
  inc(tail);
  if tail>QueueLen then tail:=tail-QueueLen;
  Queue[tail]:=pnt;
end;

Function QueueEmpty:boolean;
begin
  if head=tail then QueueEmpty:=true else QueueEmpty:=false;
end;

Procedure TopSort;
var
  i,j,now,new,nowpos:longint;
begin
  head:=0;
  tail:=0;
  for i:=1 to n do if InPnt[i]=0 then QueueIn(i);  //一开始对所有入度为0的点先入栈

  repeat
    QueueOut(now);
    nowpos:=First[now];
    write(now,' ');                 //当前点入度为0，输出
    while nowpos<>0 do
    begin
      new:=Edges[nowpos].target;
      dec(InPnt[new]);                    //被当前点指向的点入度减1
      if InPnt[new]=0 then QueueIn(new);  //如果更新后入度为零，加入队列
      nowpos:=Edges[nowpos].nextpos;
    end;
  until QueueEmpty();
end;

Begin
  Assign(input,inf);
  Reset(input);
  Assign(output,ouf);
  Rewrite(output);

  ReadData;
  TopSort;
  readln;

  Close(input);
  Close(output);
End.

