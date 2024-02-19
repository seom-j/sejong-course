-- 1) Rating, Review Number, 7 가지 상세 별점 중 우선시하는 조건 선정
CREATE TABLE want_info AS
SELECT b.Aid
FROM basic_info b
JOIN review_info r ON b.Aid = r.Aid
WHERE b.Location IN ('제주 시내', '애월읍', '조천읍', '한립음', '기타 도시')
  AND b.Type IN ('호텔', '리조트', '레지던스')
  AND b.Price <= 600000
  AND r.Rating >= 6
  AND r.`Review Number` >= 10;

SELECT COUNT(*) AS RowCount
FROM want_info;
-- 105개의 숙소가 담긴 것을 확

ALTER TABLE want_info
ADD INDEX idx_aid (Aid);

ALTER TABLE want_info
ADD FOREIGN KEY (Aid)
REFERENCES detail_info(Aid);

ALTER TABLE want_info
ADD FOREIGN KEY (Aid)
REFERENCES review_info(Aid);

-- 2) 선정된 조건들로 각각 선호 숙소 테이블에 존재하는 숙소들끼리 순위 정보 저장
-- ReviewRank
ALTER TABLE want_info
ADD COLUMN ReviewRank INT;

CREATE TEMPORARY TABLE temp_rank AS
SELECT w.Aid, RANK() OVER (ORDER BY r.`Review Number` DESC) AS ReviewRank
FROM want_info AS w
INNER JOIN Review_info AS r ON w.Aid = r.Aid;

UPDATE want_info AS w
INNER JOIN temp_rank AS tr ON w.Aid = tr.Aid
SET w.ReviewRank = tr.ReviewRank;

DROP TEMPORARY TABLE IF EXISTS temp_rank;

-- RatingRank
ALTER TABLE want_info
ADD COLUMN RatingRank INT;
-- 임시 테이블 temp_rank 생성하고 ReviewRank 값을 계산하여 저장
CREATE TEMPORARY TABLE temp_rank AS
SELECT w.Aid, RANK() OVER (ORDER BY r.Rating DESC) AS RatingRank
FROM want_info AS w
INNER JOIN Review_info AS r ON w.Aid = r.Aid;
-- want_info와 temp_rank를 조인하여 ReviewRank 값을 업데이트
UPDATE want_info AS w
INNER JOIN temp_rank AS tr ON w.Aid = tr.Aid
SET w.RatingRank = tr.RatingRank;
-- 임시 테이블 temp_rank 삭제 (있는 경우)
DROP TEMPORARY TABLE IF EXISTS temp_rank;

-- CleanlinessRank
ALTER TABLE want_info
ADD COLUMN CleanlinessRank INT;

CREATE TEMPORARY TABLE temp_rank AS
SELECT w.Aid, RANK() OVER (ORDER BY r.CleanlinessR DESC) AS CleanlinessRank
FROM want_info AS w
INNER JOIN Review_info AS r ON w.Aid = r.Aid;

UPDATE want_info AS w
INNER JOIN temp_rank AS tr ON w.Aid = tr.Aid
SET w.CleanlinessRank = tr.CleanlinessRank;

DROP TEMPORARY TABLE IF EXISTS temp_rank;

-- LocationRank
ALTER TABLE want_info
ADD COLUMN LocationRank INT;

CREATE TEMPORARY TABLE temp_rank AS
SELECT w.Aid, RANK() OVER (ORDER BY r.LocationR DESC) AS LocationRank
FROM want_info AS w
INNER JOIN Review_info AS r ON w.Aid = r.Aid;

UPDATE want_info AS w
INNER JOIN temp_rank AS tr ON w.Aid = tr.Aid
SET w.LocationRank = tr.LocationRank;

DROP TEMPORARY TABLE IF EXISTS temp_rank;

-- 3) 해당 순위들을 모두 합하여 더한 값을 최종 Personal Parameter 정보 저장
ALTER TABLE want_info
ADD COLUMN FinalParameter INT;

UPDATE want_info
SET FinalParameter = ReviewRank + RatingRank + CleanlinessRank + LocationRank;
