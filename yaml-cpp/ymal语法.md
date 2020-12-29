# YAML语法

`YAML`的设计目标就是方便人类读写，它实质上是一种通用的数据串行化格式。

基本语法规则：

+ 大小写敏感
+ 使用缩进表示层级关系
+ 缩进时不允许使用Tab键，只允许使用空格
+ 缩进的空格数目不重要，只要相同层级的元素左侧对齐即可

`#`表示注释。

`YAML`支持的数据结构有三种：

+ 对象
+ 数组
+ 纯量

### 1. 对象

对象的一组键值对，使用冒号结构表示。

```yaml
animal: pets
```

转为js如下：

```javascript
{animal: 'pets'}
```

行内对象

```yaml
hash: {name: Steve, foo: bar}
```

转为js如下：

```javascript
{hash: {name: 'Steve', foo: 'bar'}}
```

### 2. 数组

一组连词线开头的行，构成一个数组

```yaml
- Cat
- Dog
- Godfish
```

转为js如下：

```javascript
['Cat', 'Dog', 'Godfish']
```

子数组：

```yaml
- 
  - Cat
  - Dog
  - Godfish
```

转为js如下：

```javascript
[['Cat', 'Dog', 'Godfish']]
```

行内表示法

```yaml
animal: ['Cat', 'Godfish']
```

转为js如下：

```javascript
{animal: ['Cat', 'Godfish']}
```

### 3. 复合结构

对象和数组可以结合使用

```yaml
languages:
    - Ruby
    - Perl
    - Python
websites:
    YAML: yaml.org
    Ruby: ruby-lang.org
    Python: python.org
    Perl: use.perl.org
```

转化为js如下：

```javascript
{
    languages: [
        'Ruby',
        'Perl',
        'Python'
    ],
    websites: {
        YAML: 'yaml.org',
        Ruby: 'ruby-lang.org',
        Python: 'python.org',
        Perl: 'use.perl.org'
    }
}
```

### 4. 纯量

纯量是最基本的，不可再分的值

+ 字符串
+ 布尔值
+ 整数
+ 浮点数
+ Null
+ 时间
+ 日期

数值直接以字面量的形式表示：

```yaml
number: 12.30
```

布尔值用`true`或`false`表示：

```yaml
isSet: false
```

`null`使用`~`表示：

```yaml
parent: ~
```

日期：

```yaml
date: 1976-07-31
```

强制类型转换：

```yaml
e: !!str 123
f: !!str true
```

### 5. 字符串

字符串默认不使用引号表示：

```yaml
str: 这是一行字符串
```

如果字符串之中包含空格或特殊字符，需要放在引号之中

```yaml
str: '内容：字符串'
```

单引号和双引号都可以使用，双引号不会对特殊字符转义

```yaml
s1: '内容\n字符串'
s2: "内容\n字符串"
```

### 6. 引用

描点`&`和别名`*`可以用来引用。

```yaml
defaults: &defaults
    adapter: postgres
    host: localhost
development:
    database: myapp_development
    <<: *defaults
test:
    database: myapp_test
    <<: *defaults
```

转为js

```javascript
defaults:
    adapter: postgres
    host: localhost
development:
    database: myapp_development
    adapter: postgres
    host: localhost
test:
    database: myapp_test
    adapter: postgres
    host: localhost
```