Const
  MaxPoint = 9;
  MaxEdge  = 80;
  QueueLen = 80;
  inf      = 'poj2585.txt';
  ouf      = 'poj2585ans.txt';
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

  EdgesNum:integer;
  head,tail,OutQueueTime:integer;

  hasdata:string;

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
  i,j,k,l:integer;
  tmp:string;
  map:array[1..4,1..4] of integer;
  cover:array[1..9] of boolean;
begin
  Fillchar(First,SizeOf(First),0);
  Fillchar(InPnt,SizeOf(InPnt),0);
  EdgesNum:=0;

  for i:=1 to 4 do
  begin
    for j:=1 to 4 do read(map[i,j]);
    readln;
  end;
  readln(tmp);

  k:=0;
  for i:=1 to 3 do
    for j:=1 to 3 do
    begin
      inc(k);     //统计数字k被哪些数字覆盖
      fillchar(cover,sizeof(cover),false);
      if map[i,j]<>k     then cover[map[i,j]]:=true;
      if map[i,j+1]<>k   then cover[map[i,j+1]]:=true;
      if map[i+1,j]<>k   then cover[map[i+1,j]]:=true;
      if map[i+1,j+1]<>k then cover[map[i+1,j+1]]:=true;
      for l:=1 to 9 do if cover[l] then AddEdge(k,l);  //原本是k的位置现在被l覆盖了，建一条边
    end;
end;

Procedure QueueOut(var pnt:longint);
begin
  inc(OutQueueTime);
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

Function TopSort:boolean;
var
  i,now,new,nowpos:longint;
begin
  head:=0;
  tail:=0;
  OutQueueTime:=0;
  fillchar(Queue,Sizeof(Queue),0);
  for i:=1 to MaxPoint do if InPnt[i]=0 then QueueIn(i);  //一开始对所有入度为0的点先入栈

  repeat
    QueueOut(now);
    nowpos:=First[now];
    while nowpos<>0 do
    begin
      new:=Edges[nowpos].target;
      dec(InPnt[new]);                      //被当前点指向的点入度减1
      if InPnt[new]=0 then QueueIn(new);    //如果更新后入度为零，加入队列
      nowpos:=Edges[nowpos].nextpos;
    end;
  until (QueueEmpty()) or (OutQueueTime>MaxPoint); //出队次数大于最大点数，有环，终止

  if OutQueueTime=MaxPoint then TopSort:=true
                           else TopSort:=false;    //出队次数少于点数，矛盾
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  readln(hasdata);
  while hasdata<>'ENDOFINPUT' do
  begin
    ReadData;
    if TopSort then writeln('THESE WINDOWS ARE CLEAN')
               else writeln('THESE WINDOWS ARE BROKEN');
    readln(hasdata);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
