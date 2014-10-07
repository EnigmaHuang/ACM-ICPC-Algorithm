Program PrimSampleHint;   

Const
  inf      = 'PrimSample.txt';
  ouf      = 'PrimSampleOut.txt';
  PointNum = 200;
  EdgeNum  = PointNum*PointNum;

Type
  TEdge = record
            trg,len:longint;
          end;

Var
  Edges  : array[1..EdgeNum]  of TEdge;
  First  : array[1..PointNum] of longint;
  Next   : array[1..EdgeNum]  of longint;
  Heap   : array[1..PointNum] of TEdge;
  PntPos : array[1..PointNum] of longint;

  n,m,HeapTail,answer:longint;   //n为点的数目, m为边的数目
  EdgesNum:longint;

Procedure AddEdge(source,target,weight:longint);
begin
  inc(EdgesNum);
  Edges[EdgesNum].trg:=target;
  Edges[EdgesNum].len:=weight;
  //下面模拟链表里后继指向的两句
  Next[EdgesNum]:=First[source]; //Next[k]=n 表示起点为x的边下一条的存储单元在Edges[n],n=0时完毕
  First[source]:=EdgesNum;       //First[x]=k表示起点为x的边第一条的存储单元在Edges[k]
end;

Procedure ReadData;
var
  i,source,target,weight:longint;
begin
  //下面两行应该去掉的，因为调试器初始化的问题，需要加上这两行让调试器顺利运行
  i:=1;
  First[i]:=1;

  fillchar(First,SizeOf(First),0);
  fillchar(Edges,SizeOf(Edges),0);
  fillchar(Next,SizeOf(Next),0);

  readln(n,m);
  EdgesNum:=0;

  for i:=1 to m do
  begin
    readln(source,target,weight);
    AddEdge(source,target,weight);
    AddEdge(target,source,weight); //无向图
  end;
end;

Procedure GoUp(j:longint);   //二叉小根堆向上调整
var
  i:longint;
  x:TEdge;
begin
  x:=Heap[j];                          //保存要调整的节点的数据
  while j>1 do
  begin
    i:=j div 2;                        //父节点
    if Heap[i].len<=x.len then break;  //上升到极限
    Heap[j]:=Heap[i];                  //未上升到极限，交换当前节点（Heap[i]）与父节点(Heap[j])
    PntPos[Heap[j].trg]:=j;            //更新被交换的父节点在堆中的位置
    j:=i;                              //当前节点改为父节点
  end;
  Heap[j]:=x;                          //要调整的节点最终位置确定后，写入内容
  PntPos[x.trg]:=j;                    //更新要调整的节点在堆中的位置
end;

Procedure GoDown(i:longint);
var
  x:TEdge;
  j:longint;
begin
  x:=Heap[i];                          //保存要调整的节点的数据
  while i*2<=HeapTail do
  begin
    j:=i*2;                            //向下交换节点指向左孩子节点
    if (j<HeapTail) and (Heap[j+1].len<Heap[j].len) then inc(j); //右孩子更小，指向右孩子节点
    if x.len<=Heap[j].len then break;  //下降到极限
    Heap[i]:=Heap[j];                  //未下降到极限，交换当前节点 （Heap[i]）与某个子节点(Heap[j])
    PntPos[Heap[i].trg]:=i;            //更新被交换的子节点在堆中的位置
    i:=j;                              //更改当前节点
  end;
  Heap[i]:=x;                          //要调整的节点最终位置确定后，写入内容
  PntPos[x.trg]:=i;                    //更新要调整的节点在堆中的位置
end;

Procedure Pop(var point,len:longint);
begin
  //弹出堆顶数据，即为下一条生成的树枝
  point:=Heap[1].trg;
  len:=Heap[1].len;
  //维护堆
  PntPos[point]:=-1;
  Heap[1]:=Heap[HeapTail];
  PntPos[Heap[1].trg]:=1;
  Dec(HeapTail);
  GoDown(1);
end;

Procedure Prim;
var
  newpnt,cost:longint;
  i,j,now,new:longint;
begin
  for i:=1 to n do
  begin
    Heap[i].trg:=i;              //Heap[k].tgr表示某一条路径到达tgr点
    Heap[i].len:=maxlongint;     //Heap[k].len表示到达trg的某一条路径的长度
    PntPos[i]:=i;
  end;
  Heap[1].len:=0;

  answer:=0;
  HeapTail:=n;

  for i:=1 to n do
  begin
    Pop(newpnt,cost);      //弹出一条可以生成的最小边，生成新的一条树枝
    inc(answer,cost);
    now:=First[newpnt];    //当前节点为新树枝的所加入的新节点
    repeat
      new:=Edges[now].trg; //枚举一条新的边
      {
        新边所带来的新节点不在树中,且当前点到达新节点的距离小于原来某一点
        到新节点的距离（即这条边还没有被标记为可用的），则将其标记为可用的
      }
      if (PntPos[new]<>-1) and (Edges[now].len<Heap[PntPos[new]].len) then
      begin
        Heap[PntPos[new]].len:=Edges[now].len;  //标记这条路径可用
        GoUp(PntPos[new]);                      //维护堆，对所有可用路径进行排序
      end;
      now:=Next[now];                           //寻找下一条边
    until now=0;
  end;
end;

Begin
  Assign(input,inf);
  Reset(input);
  Assign(output,ouf);
  Rewrite(output);

  ReadData;
  Prim;
  write(answer);

  Close(input);
  Close(output);
End.
