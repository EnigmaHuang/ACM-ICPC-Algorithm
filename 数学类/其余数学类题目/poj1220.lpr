{
Sample input  :
1
10 62 644926447651606354382983642789370468919976641462991866984
Sample output :
10 644926447651606354382983642789370468919976641462991866984
62 HappyBirthday19941220EnigmaHuang
}

Const
  inf   = 'poj1220.txt';
  ouf   = 'poj1220ans.txt';
  Ondbg = false;
  alphabet='0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';

Var
  s,t,ans:array[0..1000] of integer;
  NewBase,OldBase,testcase:integer;
  nums:string;

Procedure Convert;
var
  i,j,d:integer;
begin
  fillchar(ans,sizeof(ans),0);
  while s[0]>=1 do
  begin
    d:=0;
    i:=1;
    t[0]:=s[0];
    while i<=s[0] do
    begin
      d:=d*OldBase+s[i];
      t[i]:=d div NewBase;
      inc(i);
      d:=d mod NewBase;
    end;
    inc(ans[0]);
    ans[ans[0]]:=d;
    i:=1;
    while (i<=t[0]) and (t[i]=0) do inc(i);
    fillchar(s,sizeof(s),0);
    for j:=i to t[0] do
    begin
      inc(s[0]);
      s[s[0]]:=t[j];
    end;
    fillchar(t,sizeof(t),0);
  end;
end;

Procedure Print;
var
  i:integer;
begin
  writeln(OldBase,' ',nums);
  write(NewBase,' ');
  for i:=ans[0] downto 1 do write(alphabet[ans[i]+1]);
  writeln;
  writeln;
end;

Procedure ReadData;
var
  i:integer;
  c:char;
begin
  read(OldBase,NewBase);
  read(c);
  readln(nums);
  s[0]:=length(nums);
  for i:=1 to length(nums) do s[i]:=pos(nums[i],alphabet)-1;
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);Reset(input);
    Assign(output,ouf);Rewrite(output);
  end;

  readln(testcase);
  while testcase>0 do
  begin
    ReadData;
    Convert;
    Print;
    dec(testcase);
  end;

  if Ondbg then
  begin
    Close(input);Close(output);
  end;
End.
