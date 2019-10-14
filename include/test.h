#ifndef TEST_H
#define TEST_H


class test
{
    public:
        test();
        virtual ~test();
        test(const test& other);
        test& operator=(const test& other);

    protected:

    private:
};

#endif // TEST_H
