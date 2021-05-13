# cpp-primer


一、数据结构(date struct)


欢迎关注个人公众号：
云铭的奇思妙想

![text](https://mmbiz.qpic.cn/mmbiz_jpg/N36xAhCmccEkFR1eT4iaKnbtlE8eBAiafUu1T7P6CEx5bsRgwwsoVia3l3DtPBicseccZTyg7ht4O3k0RGojHmTXZQ/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)


1)红黑树
    节点属性
        颜色
        父
        左子
        右子
        key

    五个性质
        红黑
        根黑
        叶黑
        红子黑
        等黑

    旋转
        左旋
            父节点变成左孩子
            右孩子变成父节点
            原来右孩子的右孩子节点移动到原父节点

        右旋
            反之


    插入
        先插入后平衡
        插入
            从根节点开始比大小
            平均比较logn次
            用递归比较简洁，虽然编译的后和循环都会翻译成循环

        平衡
            不平衡情况3种
                父、叔都是红色
                    让父叔变黑、爷变红

                父红，右叔是黑色，新节点插入在父右
                    以父左旋，变为情况3

                父红，右叔是黑色，新节点插入在父左
                    以爷右旋，原爷变黑，父变红。







