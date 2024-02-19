-- 1) Location 분석: 동네별 숙소 수 파악
SELECT Location, COUNT(*) AS Count
FROM basic_info
GROUP BY Location order by Count desc;
-- 총 8개 종류의 lotation 존재
-- 한경면, 우도는 숙소가 얼마 없음


--2) Price 분석: 가격 분포 파악
SELECT MIN(Price) AS MinPrice, MAX(Price) AS MaxPrice, AVG(Price) AS AvgPrice, COUNT(*) AS Count 
FROM basic_info;
-- 5만원대 ~ 200만원대까지 아주 다양한 가격 존재

SELECT
  CONCAT(FLOOR((Price - 50000) / 50000) * 50000 + 50000, '-', FLOOR((Price - 50000) / 50000) * 50000 + 99999) AS PriceRange,
  COUNT(*) AS Count
FROM basic_info
WHERE Price >= 50000 AND Price <= 2050000
GROUP BY FLOOR((Price - 50000) / 50000)
ORDER BY FLOOR((Price - 50000) / 50000);
-- 그러나 40만원 이하가 대부분이라는 것을 확인할 수 있음


-- 3) Type 분석: 숙소 유형별 숙소 수 파악
SELECT Type, COUNT(*) AS Count
FROM basic_info
GROUP BY Type order by Count desc;
-- 총 11개의 숙소 유형 존재
-- 비앤비, 빌라, 모텔은 하나씩 뿐이며, 대부분 호텔, 홀리데이 홈이라는 것을 알 수 있음


-- 4) Location-Price: 동네별 가격대 파악
SELECT l.Location, AVG(b.Price) AS AveragePrice
FROM location_info l
LEFT JOIN basic_info b ON l.Location = b.Location
GROUP BY l.Location
ORDER BY AveragePrice desc;
-- 지역별 평균 가격
-- 우도, 구좌읍, 한립읍이 가격대가 있는 편이며
-- 제주 시내, 한경면, 애월읍, 조천읍이 상대적으로 저렴한 편


-- 5) Type-Price: 숙소 유형별 가격 분포 파악
SELECT t.Type, AVG(b.Price) AS AveragePrice
FROM type_info t
LEFT JOIN basic_info b ON t.Type = b.Type
GROUP BY t.Type
ORDER BY AveragePrice asc;
-- 모텔, 호스텔 게스트하우스가 저렴한 편이며
-- 컨트리 하우스, 레지던스, 호텔, 아파트, 홀리데이 홈, 리조트, 빌라, 비앤비 순으로 가격대가 높아짐


-- 6) Type-Location: 동네별 숙소 유형 분포 파악
SELECT Location, Type, COUNT(*) AS Count
FROM basic_info
GROUP BY Location, Type;

SELECT
  Location,
  SUM(CASE WHEN Type = '비앤비' THEN Count END) AS '에어비앤비',
  SUM(CASE WHEN Type = '호텔' THEN Count END) AS '호텔',
  SUM(CASE WHEN Type = '게스트하우스' THEN Count END) AS '게스트하우스',
  SUM(CASE WHEN Type = '레지던스' THEN Count END) AS '레지던스',
  SUM(CASE WHEN Type = '리조트' THEN Count END) AS '리조트',
  SUM(CASE WHEN Type = '아파트' THEN Count END) AS '아파트',
  SUM(CASE WHEN Type = '컨트리 하우스' THEN Count END) AS '컨트리 하우스',
  SUM(CASE WHEN Type = '모텔' THEN Count END) AS '모텔',  
  SUM(CASE WHEN Type = '빌라' THEN Count END) AS '빌라',
  SUM(CASE WHEN Type = '호스텔' THEN Count END) AS '호스텔',
  SUM(CASE WHEN Type = '홀리데이 홈' THEN Count END) AS '홀리데이 홈'
FROM
(
  SELECT Location, Type, COUNT(*) AS Count
  FROM basic_info
  GROUP BY Location, Type
) AS subquery
GROUP BY Location;
-- 전체적으로 제주 시내에 다양한 종류의 숙소가 많이 존재
-- 한경면은 숙소 자체가 얼마 없음


-- 7) Rating: 별점 분포 파악
SELECT 
  FLOOR(Rating/2)*2 AS RatingRangeFirstValue,
  COUNT(*) AS CountRating
FROM review_info
WHERE Rating <= 10
GROUP BY FLOOR(Rating/2)*2
ORDER BY RatingRangeFirstValue;
-- 분포를 보아, 무난한 숙소의 경우 6이라고 판단


-- 8) Review Number: 리뷰 수 분포 파악
SELECT 
    MAX(`Review Number`) AS Maximum,
    MIN(`Review Number`) AS Minimum,
    AVG(`Review Number`) AS Average
FROM review_info;

SELECT 
    FLOOR((`Review Number`) / 100) * 100 AS RangeStart,
    FLOOR((`Review Number`) / 100) * 100 + 100 AS RangeEnd,
    COUNT(*) AS Count
FROM review_info
WHERE `Review Number` <= 2700
GROUP BY FLOOR((`Review Number`) / 100);
-- 0에서 100의 분포가 가장 몰려있는 것을 확인할 수 있음
-- review 개수는 적절히 판단할 수 있는 10개 이상일 경우 괜찮을 것이라 판단


-- 9) Rating-Location: 지역별 별점대 파악
select * from review_info;
SELECT basic_info.Location, AVG(review_info.Rating) AS AvgRating
FROM basic_info
JOIN review_info ON basic_info.Aid = review_info.Aid
GROUP BY basic_info.Location
order by AvgRating desc;
-- 한경면, 구좌읍의 별점이 좋지 못한 것을 확인할 수 있음


-- 10) Rating-Type: 숙소 유형별 별점대 파악
-- 숙소 유형별 리뷰 분석
select * from review_info;
SELECT basic_info.Type, AVG(review_info.Rating) AS AvgRating
FROM basic_info
JOIN review_info ON basic_info.Aid = review_info.Aid
GROUP BY basic_info.Type
order by AvgRating desc;
-- 빌라와 비앤비는 리뷰가 존재하지 않고, 컨트리하우스와 아파트의 별점이 좋지 못한 것을 확인할 수 있음


-- 11) Rating-Price: 별점과 가격간의 상관관계 파악
-- 상관관계를 구하는 프로시져 사용 
DELIMITER //

CREATE PROCEDURE CalculateCorrelation(
  IN columnName VARCHAR(255),
  IN priceLimit INT,
  OUT correlation DECIMAL(10, 4)
)
BEGIN
  SET @correlation = 0;

  SET @query = CONCAT('
    SELECT 
      (
        (N * SUM(Price * ', columnName, ') - SUM(Price) * SUM(', columnName, ')) /
        (SQRT((N * SUM(POW(Price, 2)) - POW(SUM(Price), 2)) * (N * SUM(POW(', columnName, ', 2)) - POW(SUM(', columnName, '), 2))))
      ) INTO @correlation
    FROM
      basic_info, (SELECT COUNT(*) AS N FROM basic_info) AS subquery, review_info
    WHERE
      basic_info.Aid = review_info.Aid
      AND Price <= ', priceLimit, '
  ');

  PREPARE stmt FROM @query;
  EXECUTE stmt;
  DEALLOCATE PREPARE stmt;

  SELECT @correlation INTO correlation;
END //

DELIMITER ;

-- 리뷰 개수와 가격의 상관관계
CALL CalculateCorrelation('`Review Number`', 3000000, @correlationValue);
select @correlationValue;
-- 전체 범위에서 (최대 200만원대였기에) 음수가 나오는 것을 확인할 수 있음

CALL CalculateCorrelation('`Review Number`', 400000, @correlationValue);
select @correlationValue;
-- 가격대를 낮추니 양의 상관관계를 지니며, 점점 더 낮아질수록 양의 상관관계가 높아지는 것을 확인할 수 있음
-- 과도하게 높은 가격대의 경우, 사람들이 가기 꺼려하여 리뷰가 얼마 없는 것으로 추정

-- 별점과 가격의 상관관계
CALL CalculateCorrelation('Rating', 3000000, @correlationValue);
select @correlationValue;
-- 마찬가지로 전체 범위에서 (최대 200만원대였기에) 음수가 나오는 것을 확인할 수 있음
CALL CalculateCorrelation('Rating', 400000, @correlationValue);
select @correlationValue;
-- 가격대를 낮추니 양의 상관관계를 지니며, 점점 더 낮아질수록 양의 상관관계가 높아지는 것을 확인할 수 있음
-- 가격대가 과도하게 높을 경우 사람들의 원하고자 하는 바가 많아져 별점이 좋지 않은 것으로 추정됨

-- 각 별점과 가격의 상관관계 파악
CALL CalculateCorrelation('StaffFriendlinessR', 3000000, @correlationValue0);
CALL CalculateCorrelation('Facilities', 3000000, @correlationValue1);
CALL CalculateCorrelation('CleanlinessR', 3000000, @correlationValue2);
CALL CalculateCorrelation('ComfortR', 3000000, @correlationValue3);
CALL CalculateCorrelation('`Cost-effectivenessR`', 3000000, @correlationValue4);
CALL CalculateCorrelation('LocationR', 3000000, @correlationValue5);
CALL CalculateCorrelation('`Free Wi-FiR`', 3000000, @correlationValue6);
select @correlationValue0 as StaffFriendlinessR, @correlationValue1 as Facilities, @correlationValue2 as CleanlinessR, @correlationValue3 as ComfortR,
@correlationValue4 `Cost-effectivenessR`, @correlationValue5 as LocationR, @correlationValue6 as `Free Wi-FiR`;

CALL CalculateCorrelation('StaffFriendlinessR', 400000, @correlationValue0);
CALL CalculateCorrelation('Facilities', 400000, @correlationValue1);
CALL CalculateCorrelation('CleanlinessR', 400000, @correlationValue2);
CALL CalculateCorrelation('ComfortR', 400000, @correlationValue3);
CALL CalculateCorrelation('`Cost-effectivenessR`', 400000, @correlationValue4);
CALL CalculateCorrelation('LocationR', 400000, @correlationValue5);
CALL CalculateCorrelation('`Free Wi-FiR`', 400000, @correlationValue6);
select @correlationValue0 as StaffFriendlinessR, @correlationValue1 as Facilities, @correlationValue2 as CleanlinessR, @correlationValue3 as ComfortR,
@correlationValue4 `Cost-effectivenessR`, @correlationValue5 as LocationR, @correlationValue6 as `Free Wi-FiR`;
-- 동일하게, 전체 가격대에선 음의 상관계수가 나왔으나, 가격대 범위를 낮출수록 양의 상관계수가 보이는 것을 확인할 수 있음
-- 따라서 너무 높지 않은 가격대라면, 어느정도 가격대가 있는 곳에 머무르는 것이 만족도를 높일 것으로 추정

-- 추가적으로 가격대가 있는 빌라와 비앤비의 리뷰가 존재하지 않은 영향도 있다고 보임


/*
결론 : 
<Location>
한경면, 우도는 숙소의 양이 많지 않아 비교 대상이 없으므로 제외

<Price>
적당한 가격대에 다양한 숙박 옵션들을 선택할 수 있는 40만원 이하로 설정

<Type>
비교 대상이 없는 비앤비, 빌라, 모텔 제외

<Type-Price>
공동 생활이 필요하여 호스텔과 게스트하우스는 저렴한 것으로 파악됨
그러나 이번 여행에서 공동 생활을 바라지는 않으므로 제외 (같은 이유로 홀리데이홈도 제외!)

<Rating>
분포를 보아, 무난할 경우 6정도의 점수를 지닌다고 파악
최소 6 이상이라는 조건 추가

<Review Number>
분포를 보아, 0~100사이가 가장 많은 것을 확인
최소한으로 숙소를 판단할 수 있는 10 이상인 숙소 선호

<Review-Location>
별점이 많이 좋지 못한 한경면, 구좌읍 제외

<Review-Type>
별점이 좋지 못한 컨트리하우스, 아파트 제외
빌라/비앤비 리뷰 존재 X, 제외

<Review-Price>
전체적으로 상관관계를 파악해보는 시간을 가짐
모든 가격대에서는 가격과 리뷰들이 음의 상관관계를 지녔지만,
대부분의 숙소가 존재하는 40만원 이하 구간에서는 양의 상관관계를 가짐
특히나 가격대가 내려갈수록 양의 상관관계가 더욱 오르는 것을 확인할 수 있었음

이는 가격대가 어느정도 있어야 숙소의 질이 좋아진 다는 것을 파악할 수 있었고,
일정하게 상관관계가 오르고 내리는 것을 보아 다양한 상세 리뷰의 신뢰도가 있다는 것을 확인할 수 있었음
*/
