Const
  MaxNum = 64;
  inf    = 'poj1011.txt';
  ouf    = 'poj1011ans.txt';
  Ondbg  = true;

Var
  stick:array[1..MaxNum] of integer;
  visit:array[1..MaxNum] of boolean;
  n,TargetLen,MaxLen,SumLen,k:integer;

Procedure QSort(l,r:integer);
var
  i,j,mid,swap:integer;
begin
  i:=l;
  j:=r;
  mid:=stick[(i+j) div 2];
  repeat
    while stick[i]>mid do inc(i);
    while stick[j]<mid do dec(j);
    if i<=j then
    begin
      swap:=stick[i];
      stick[i]:=stick[j];
      stick[j]:=swap;
      inc(i);dec(j);
    end;
  until i>j;
  if l<j then QSort(l,j);
  if i<r then QSort(i,r);
end;

Function DFS(NowLen,SearchStart,Used:integer):boolean; //当前组合长度，搜索起始位置，已用段数
var
  nowl,i:integer;
begin
  if Used=n then exit(true);

  nowl:=0;
  for i:=SearchStart to n do
  begin
    if (visit[i]) or (stick[i]=nowl) then continue;    //剪枝3：不重复搜索相同的长度

    visit[i]:=true;
    if (NowLen+stick[i]<TargetLen) then
    begin
      if DFS(NowLen+stick[i],i,Used+1) then exit(true)
      else nowl:=stick[i];
    end
    else if (NowLen+stick[i]=TargetLen) then
    begin
      if DFS(0,1,Used+1) then exit(true)
      else nowl:=stick[i];
    end;
    visit[i]:=false;

    //网上看回来的，不加会TLE
    //剪枝4：如果构建新的一支时，遇到的第一根可用的段没有被使用，则肯定不会被再用，不行
    if NowLen=0 then break;
  end;
  exit(false);
end;

Procedure Solve;
var
  flag:boolean;
begin
  flag:=false;
  MaxLen:=stick[1];
  for TargetLen:=MaxLen to (SumLen div 2) do //剪枝1：如果棒的数目大于1，则必
  begin                                      //不超过总长的一半，必不小于最长段
    if (SumLen mod TargetLen)=0 then         //剪枝2：棒长必须是总长的约数
      if DFS(0,1,0) then
      begin
        flag:=true;
        break;
      end;
  end;
  if flag=false then TargetLen:=SumLen;
  writeln(TargetLen);
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);Reset(input);
    Assign(output,ouf);Rewrite(output);
  end;

  readln(n);
  while n<>0 do
  begin
    SumLen:=0;
    fillchar(visit,sizeof(visit),0);
    for k:=1 to n do
    begin
      read(stick[k]);
      inc(SumLen,stick[k]);
    end;
    QSort(1,n);
    Solve;
    readln(n);
  end;

  if Ondbg then
  begin
    Close(input);Close(output);
  end;
End.
