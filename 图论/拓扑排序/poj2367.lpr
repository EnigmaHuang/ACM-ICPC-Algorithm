Const
  MaxPoint = 100;
  MaxEdge  = 99*100;
  QueueLen = MaxPoint+1;
  inf      = 'poj2367.txt';
  ouf      = 'poj2367ans.txt';
  Ondbg    = true;

Type
  TEdge = record
            target,nextpos:integer;
          end;

Var
  Edges:array[1..MaxEdge]  of TEdge;     //边数组，模拟邻接表
  First:array[1..MaxEdge]  of integer;   //从该顶点出发的边在数组中的最后位置
  Queue:array[1..QueueLen] of integer;   //队列堆栈记录优化
  InPnt:array[1..MaxPoint] of integer;   //各点的入度数

  n,m,EdgesNum:integer;
  head,tail:integer;

Procedure AddEdge(src,trg:integer);
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
  i,j,trg:integer;
begin
  Fillchar(First,SizeOf(First),0);
  Fillchar(InPnt,SizeOf(InPnt),0);
  EdgesNum:=0;

  readln(n);
  for i:=1 to n do
  begin
    read(trg);
    while trg<>0 do
    begin
      AddEdge(i,trg);
      read(trg);
    end;
    readln;
  end;
end;

Procedure QueueOut(var pnt:integer);
begin
  inc(head);
  if head>QueueLen then head:=head-QueueLen;
  pnt:=Queue[head];
end;

Procedure QueueIn(pnt:integer);
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
  i,j,now,new,nowpos:integer;
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
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  ReadData;
  TopSort;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
