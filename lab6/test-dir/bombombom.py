def summa(n1: int):
    def s1(n2: int):
        def s2(n3: int):
            def s3(n4: int):
                def s4(n5: int):
                    def s5(n6: int):
                        def wrapper(n: int):
                            return sum([n, n1, n2, n3, n4, n5, n6])
                        return wrapper
                    return s5
                return s4
            return s3
        return s2
    return s1


def main():
    moya_summa = summa(1)
    moya_summa = moya_summa(2)
    moya_summa = moya_summa(3)
    moya_summa = moya_summa(4)
    moya_summa = moya_summa(10)
    moya_summa = moya_summa(30)
    moya_summa = moya_summa(50)

    print(f'MOYA SUMMA: {moya_summa}')


if __name__ == '__main__':
    main()
